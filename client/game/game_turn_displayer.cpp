#include "game_turn_displayer.h"
#include "constants.h"

GameTurnDisplayer::~GameTurnDisplayer() {
    display.remove(header);
    for (auto text: turn_wheel)
        display.remove(text);
}
GameTurnDisplayer::GameTurnDisplayer(
    GameDisplay& display,
    const std::vector<int>& client_turn_order,
    int x, int y
) : 
display(display),
x(x),y(y),
header(nullptr),
client_life(),
turn_wheel(),
client_order()
{
    header = display.new_text("TURNOS:",x, y, TextAlign::left, TextLayer::UI, TextType::gametext, 0xFFFFFF);
    std::cout << "Client size: " << client_turn_order.size() << std::endl;
    int client_count = client_turn_order.size();
    for (int i = 0; i < client_count; i++) {
        int curr_cli = client_turn_order[i];

        std::cout << "Added on order: " << i << "client: " << curr_cli  << std::endl;
        client_order.emplace(curr_cli, i);
        client_life.emplace_back(curr_cli);

        turn_wheel.emplace_back(display.new_text(
            "Jugador " + std::to_string(client_turn_order[i]),
            x+8, y+16+i*16, TextAlign::left, TextLayer::UI, TextType::gametext, COLOR_BY_CLIENT[i]
        ));
    }
}

void GameTurnDisplayer::update(const std::vector<WormDto>& worms, const int active) {
    int client_count = turn_wheel.size();
    std::cout << "Before newvals: " << std::endl;
    std::vector<int> newvals(client_count);

    for (auto& worm: worms) {
        if (worm.life > 0)
            newvals[client_order[worm.client_id]] += worm.life;
    }

    std::cout << "Before for: " << std::endl;
    for (int i = 0; i < client_count; i++) {
        std::cout << "Text is: " << turn_wheel[i] << std::endl;
        auto text = turn_wheel[i];
        std::cout << "Client order is: " << client_order[active] << std::endl;
        if (active > 0 && i != client_order[active]) {
            text->set_pos(x+8,text->y);
        } else {
            text->set_pos(x+16,text->y);
        }

        std::cout << "Client life is: " << client_life[i] << std::endl;
        if (client_life[i] != newvals[i]) {
            std::cout << "Client new life is: " <<  newvals[i] << std::endl;
            const std::string val(
                "Jugador " +
                NAME_BY_CLIENT[i] +
                ": "+ std::to_string(newvals[i])
            );
            text->update(val);
            client_life[i] = newvals[i];
        }
    }
}
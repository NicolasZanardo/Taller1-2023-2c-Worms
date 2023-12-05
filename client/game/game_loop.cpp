#include "game_loop.h"
#include "Game/game_clock.h"

GameLoop::GameLoop(
    GameDisplay &display,
    Queue<std::shared_ptr<ClientGameStateDTO>> &state_queue,
    const std::shared_ptr<ClientGameStateDTO> &initial_game_state_dto,
    ClientGameState &game_state
)
    : display(display), state_queue(state_queue) {
    game_state.load(initial_game_state_dto);
}

void GameLoop::execute(EventHandler &event_handler, ClientGameState &game_state) {
    bool running = true;
    GameClock clock(CLIENT_FPS);

    while (running) {
        running = event_handler.handleEvents();
        update(game_state);
        display.update(clock.delta());
        clock.sync();
    }
}

void GameLoop::update(ClientGameState &game_state) {
    std::shared_ptr<ClientGameStateDTO> game_state_dto;
/*    //std::cout << "Inicializando estado del juego.\n";
    state_queue.try_pop(game_state_dto);
    if (game_state_dto == nullptr) {
        return;
    } else {*/
        bool receive_new_state = false;
        while (state_queue.try_pop(game_state_dto)) {
            receive_new_state = true;
        }
        if (receive_new_state) {
            game_state.update(game_state_dto);
        }
    //}
}

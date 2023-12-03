#include "TurnManager.h"
TurnManager::~TurnManager() {
    for (auto cli : clients.values) {
        delete(cli);
    }
}
TurnManager::TurnManager(
    std::vector<std::shared_ptr<Projectile>>& projectiles,
    std::unordered_map<int, std::shared_ptr<Worm>>& worms,
    int game_time, int turn_lenght, int post_action_time,
    int time_rate
) : projectiles(projectiles), worms(worms),
    turn_lenght(turn_lenght), turn_remaining_time(turn_lenght),
    game_remaining_time(game_time), post_action_time(post_action_time),
    time_rate(time_rate), on_overtime(false) 
    { }

int TurnManager::current_client() {
    return clients.current()->client_id;
}

std::shared_ptr<Worm> TurnManager::current_entity() {
    return clients.current()->entities.current();
}

void TurnManager::next_turn() {
    clients.current()->entities.next();
    clients.next();
}

void TurnManager::remove_dead_worms() {
    for (auto cli : clients.values) {
        cli->entities.remove_if([](auto worm) {
            return !worm->is_alive();
        });
    }

    clients.remove_if([](auto cli) {
        return cli->entities.values.size() == 0;
    });
}

void TurnManager::remove(int entity_id) {
    int entity = current_entity()->Id();

    for (auto cli : clients.values) {
        cli->entities.remove_if([entity_id](auto worm) {
            return worm->Id() == entity_id;
        });
    }

    clients.remove_if([](auto cli) {
        return cli->entities.values.size() == 0;
    });

    if (entity == entity_id)
        next_turn();
}

void TurnManager::add_player(int client_id, std::shared_ptr<Worm> worm) {
    for (auto cli : clients.values) {
        if (cli->client_id == client_id) {
            cli->entities.values.emplace_back(worm);
            return;
        }
    }

    auto client = new ClientTurn(client_id);
    clients.values.emplace_back(client);
    client->entities.values.emplace_back(worm);
}

void TurnManager::update(int delta_time) {
    //remove_dead_worms();
    if (game_has_ended()) {
        return;
    }

    turn_remaining_time -= delta_time * time_rate;
    game_remaining_time -= delta_time * time_rate;

    if (!on_overtime && current_entity()->has_done_ending_turn_action()) {
        turn_remaining_time = post_action_time;
        //state = TurnState::ADDITIONAL_TURN_TIME;
        on_overtime = true;
        return;
    }

    if (turn_remaining_time > 0) {
        return;
    }

    if (projectiles.size() > 0)
        return;
    for (auto [id, worm] : worms) {
        if (!worm->is_still()) {
            return;
        }
    }
    
    
    current_entity()->on_turn_ended();
    next_turn();
    turn_remaining_time = turn_lenght;
    on_overtime = false;
}

bool TurnManager::game_has_ended() {
    return clients.values.size() <= 1 || game_remaining_time <= 0;
}

int TurnManager::get_game_remaining_time() {
    return game_remaining_time;
}

int TurnManager::get_turn_remaining_time() {
    return turn_remaining_time;
}

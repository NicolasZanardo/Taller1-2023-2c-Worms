#include "TurnManager.h"
#include <iostream>

TurnManager::~TurnManager() {
    for (auto cli: clients_turns) {
        delete (cli);
    }
}

TurnManager::TurnManager(
    std::vector<std::shared_ptr<Projectile>> &projectiles,
    std::unordered_map<int, std::shared_ptr<Worm>> &worms,
    int game_time, int turn_lenght, int post_action_time,
    int time_rate
) : state(TurnState::TURN_TIME),
    projectiles(projectiles), worms(worms),
    turn_lenght(turn_lenght), turn_remaining_time(turn_lenght),
    game_remaining_time(game_time), post_action_time(post_action_time),
    time_rate(time_rate), on_overtime(false) {}

void TurnManager::update(int it) {
    //remove_dead_worms();
    if (game_has_ended()) {
        return;
    }

    game_remaining_time -= it * time_rate;

    if (state == TurnState::WAITING_TO_START_NEXT_TURN) {
        std::cout << "Waiting to advance turn\n";
        if (worms_are_still() && projectiles.empty()) {
            std::cout << "advance turn\n";
            next_turn();
        }
    } else {
        step_turn_time(it);
    }
}

void TurnManager::step_turn_time(const int it) {
    turn_remaining_time -= it * time_rate;
    std::cout << "turn time left: " << turn_remaining_time << "\n";
    std::cout << "Inside turn manager call to get current worm\n";
    auto current_worm = get_current_worm();
    std::cout << "After getting current worm\n";
    if (turn_remaining_time <= 0) {
        if (current_worm) {
            std::cout << "On turn ended callback\n";
            current_worm->on_turn_ended();
        }
        std::cout << "After On turn ended callback\n";
        state = TurnState::WAITING_TO_START_NEXT_TURN;
        std::cout << "Set waiting to advance to true\n";
    } else {
        // If it has done an ending turn action but we already are in POST_ACTION_TIME we dont want to enter
        if (current_worm && current_worm->has_done_ending_turn_action() && state == TurnState::TURN_TIME) {
            turn_remaining_time = post_action_time;
            state = TurnState::POST_ACTION_TIME;
        }
    }
}

int TurnManager::current_client() {
    if (state == TurnState::WAITING_TO_START_NEXT_TURN)
        return -1;
    std::cout << "Asked for current client\n";
    return clients_turns[current_client_idx]->client_id;
}

std::shared_ptr<Worm> TurnManager::get_current_worm() {
    if (state == TurnState::WAITING_TO_START_NEXT_TURN) {
        std::cout << "Returning nullptr\n";
        return nullptr;
    }
    auto worm = clients_turns[current_client_idx]->get_current_worm();
    std::cout << "The worm I got from client turn was is alive:" << worm->is_alive() << "and is active" << worm->IsActive() << "\n";
    std::cout << "The worm I got from client turn was:" << worm->Id() << "\n";
    return worm;
}

int TurnManager::get_current_worm_id() {
    auto curr_worm = get_current_worm();
    if (curr_worm) {
        return curr_worm->Id();
    } else {
        return -1;
    }
}

void TurnManager::next_turn() {
    state = TurnState::TURN_TIME;
    // If current was last client and it was removed, current index should go to beginning
    if (current_client_idx >= clients_turns.size()) {
        current_client_idx = 0;
        std::cout << "Current client index was last and now is 0" << std::endl;
    } else {
        clients_turns[current_client_idx]->advance_next_worm();
        std::cout << "Current client index was: " << current_client_idx << std::endl;
        current_client_idx++;
        if (current_client_idx >= clients_turns.size())
            current_client_idx = 0;
        std::cout << "Now current client index is: " << current_client_idx << std::endl;
    }
    turn_remaining_time = turn_lenght;
}

void TurnManager::remove_dead_worms() {
    /* for (auto cli : clients.values) {
         cli->entities.remove_if([](auto worm) {
             return !worm->is_alive();
         });
     }

     clients.remove_if([](auto cli) {
         return cli->entities.values.size() == 0;
     });*/
}

void TurnManager::remove(int worm_id_to_remove) {
    int client_turn_idx_to_be_removed = -1;
    bool removing_current_worm = get_current_worm_id() == worm_id_to_remove;

    for (auto client_turn: clients_turns) {
        client_turn->remove(worm_id_to_remove);

        if (client_turn->worms.empty()) {
            // Store the index of the ClientTurn to be removed
            client_turn_idx_to_be_removed = std::distance(clients_turns.begin(), std::find(clients_turns.begin(), clients_turns.end(), client_turn));
        }
    }

    // If the client_turn was left with 0 worms
    if (client_turn_idx_to_be_removed != -1) {

        // If it was previous to the current client_turn we should decrease current_client_idx by one
        if (client_turn_idx_to_be_removed < current_client_idx) {
            current_client_idx--;
        }

        // Erase the ClientTurn
        clients_turns.erase(clients_turns.begin() + client_turn_idx_to_be_removed);
    }

    // After all was correctly set up, if we removed the current worm pass to next turn
    if (removing_current_worm)
        next_turn();
}

/*    int entity = current_entity()->Id();

    for (auto cli : clients.values) {
        cli->entities.remove_if([entity_id](auto worm) {
            return worm->Id() == entity_id;
        });
    }

    clients.remove_if([](auto cli) {
        return cli->entities.values.size() == 0;
    });

    if (entity == entity_id)
        next_turn();*/


void TurnManager::add_player(int client_id, const std::shared_ptr<Worm> &worm) {
    std::cout << "Adding player: " << client_id << " and worm: " << worm->Id() << std::endl;
    // If client was already on the turn manager
    for (auto cli: clients_turns) {
        if (cli->client_id == client_id) {
            std::cout << "Player: " << client_id << " already existed so emplacing worm: " << worm->Id() << std::endl;
            cli->worms.push_back(worm);
            return;
        }
    }
    // Else add him
    auto client = new ClientTurn(client_id);
    std::cout << "Player: " << client_id << " didnt exist so adding player with worm: " << worm->Id() << std::endl;
    clients_turns.push_back(client);
    client->worms.push_back(worm);
}

bool TurnManager::game_has_ended() const {
    if (clients_turns.size() <= 1 || game_remaining_time <= 0) {
        std::cout << "Game ended\n";
        // current_client_id = -1;
        // current_worm_id = -1;
        return true;
    }
    return false;
}

int TurnManager::get_game_remaining_time() const {
    return game_remaining_time;
}

int TurnManager::get_turn_remaining_time() const {
    return turn_remaining_time;
}

bool TurnManager::worms_are_still() {
    for (const auto &[_, worm]: worms) {
        if (!worm->is_still()) {
            return false;
        }
    }
    return true;
}

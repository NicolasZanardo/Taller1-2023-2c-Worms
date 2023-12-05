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
    turn_length(turn_lenght), turn_remaining_time(turn_lenght),
    game_remaining_time(game_time), post_action_time(post_action_time),
    time_rate(time_rate) {}

void TurnManager::update(int it) {
    if (game_has_ended()) {
        return;
    }

    game_remaining_time -= it * time_rate;

    if (state == TurnState::WAITING_TO_START_NEXT_TURN) {
        if (worms_are_still() && projectiles.empty()) {
            next_turn();
        }
    } else {
        step_turn_time(it);
    }
}

void TurnManager::step_turn_time(const int it) {
    turn_remaining_time -= it * time_rate;
    auto current_worm = get_current_worm();
    if (turn_remaining_time <= 0) {
        if (current_worm) {
            current_worm->on_turn_ended();
        }
        state = TurnState::WAITING_TO_START_NEXT_TURN;
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
    return clients_turns[current_client_idx]->client_id;
}

std::shared_ptr<Worm> TurnManager::get_current_worm() {
    if (state == TurnState::WAITING_TO_START_NEXT_TURN) {
        return nullptr;
    }
    auto worm = clients_turns[current_client_idx]->get_current_worm();
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
    clients_turns[current_client_idx]->advance_next_worm();
    current_client_idx++;
    if (current_client_idx >= clients_turns.size())
        current_client_idx = 0;
    turn_remaining_time = turn_length;
}

void TurnManager::remove(int worm_id_to_remove) {
    int client_turn_idx_to_be_removed = -1;
    bool removing_current_worm = get_current_worm_id() == worm_id_to_remove;

    for (auto client_turn: clients_turns) {
        client_turn->remove(worm_id_to_remove);

        if (client_turn->worms.empty()) {
            // Store the index of the ClientTurn to be removed
            client_turn_idx_to_be_removed = std::distance(clients_turns.begin(),
                                                          std::find(clients_turns.begin(), clients_turns.end(),
                                                                    client_turn));
        }
    }
    bool removing_current_client = client_turn_idx_to_be_removed == current_client_idx;

    // If the client_turn was left with 0 worms
    if (client_turn_idx_to_be_removed != -1) {

        // If it was previous to the current client_turn we should decrease current_client_idx by one
        if (client_turn_idx_to_be_removed < current_client_idx) {
            current_client_idx--;
        } else if (removing_current_client && current_client_idx == (clients_turns.size() - 1)) {
            current_client_idx = 0;
        }

        // Erase the ClientTurn
        clients_turns.erase(clients_turns.begin() + client_turn_idx_to_be_removed);
    }

    // After all was correctly set up, if we removed the current worm pass to next turn
    if (removing_current_worm) {
        if (!removing_current_client) {
            current_client_idx++;
            if (current_client_idx >= clients_turns.size())
                current_client_idx = 0;
        }

        state = TurnState::TURN_TIME;
        turn_remaining_time = turn_length;
    }
}

void TurnManager::add_player(int client_id, const std::shared_ptr<Worm> &worm) {
    // If client was already on the turn manager
    for (auto cli: clients_turns) {
        if (cli->client_id == client_id) {
            std::cout << "Added worm: " << worm->Id() << "to player: " << client_id << std::endl;
            cli->worms.push_back(worm);
            return;
        }
    }
    // Else add him
    std::cout << "Added player: " << client_id << "with worm: " << worm->Id()<< std::endl;
    auto client = new ClientTurn(client_id);
    clients_turns.push_back(client);
    client->worms.push_back(worm);
}

bool TurnManager::game_has_ended() const {
    if (clients_turns.size() <= 1 || game_remaining_time <= 0)
        return true;
    return false;
}

int TurnManager::get_game_remaining_time() const {
    return game_remaining_time;
}

int TurnManager::get_turn_remaining_time() const {
    return turn_remaining_time;
}

std::vector<int> TurnManager::get_order() {
    if (clients_turns.empty()) {
        return std::vector<int>();
    }

    std::vector<int> order;
    order.reserve(clients_turns.size());
    for (auto client_turn: clients_turns) {
        order.push_back(client_turn->client_id);
    }
    return order;
}

bool TurnManager::worms_are_still() {
    for (const auto &[_, worm]: worms) {
        if (!worm->is_still()) {
            return false;
        }
    }
    return true;
}

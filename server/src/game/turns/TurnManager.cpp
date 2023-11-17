#include "TurnManager.h"
#include <iostream>

TurnManager::TurnManager(int rate): rate(rate), clients_ids_to_worms_ids_iterator() {}

void TurnManager::update(const int it) {
    // Check if the game time has run out
    if (game_time_left <= 0) {
        return;
    }

    // Update times
    game_time_left -= it * rate;
    if (!waiting_to_start_next_turn) {
        turn_time_left -= it * rate;
         // std::cout << "Time left on turn: " << turn_time_left << "\n";
        // Check if the turn time has run out
        if (turn_time_left <= 0) {
            end_actual_turn();
        }
    } else { // TODO THIS IS A HARDCODED TIME NOW BUT SHOULD UNTIL ALL EXPLOSIONS AND WORMS MOVING HAS ENDED
        inside_turns_time_left -= it * rate;
         // std::cout << "Time left inside turns: " << inside_turns_time_left << "\n";
        // Check if the inside turns time has run out
        if (inside_turns_time_left <= 0) {
            advance_to_next_turn();
        }
    }

}

void TurnManager::end_actual_turn() {
    waiting_to_start_next_turn = true;
    inside_turns_time_left = inside_turns_duration;
}

void TurnManager::advance_to_next_turn() {
    waiting_to_start_next_turn = false;
    turn_time_left = turn_duration;

    // Find the iterator for the current client
    auto currentClientIterator = clients_ids_to_worms_ids_iterator.find(current_client_id);

    // If the current client was not found or it was the last client, reset to the first client
    if (currentClientIterator == clients_ids_to_worms_ids_iterator.end() || std::next(currentClientIterator) == clients_ids_to_worms_ids_iterator.end()) {
        currentClientIterator = clients_ids_to_worms_ids_iterator.begin();
    } else {
        // Otherwise, move to the next client
        currentClientIterator++;
    }

    // Update currentClientId to the next client
    current_client_id = currentClientIterator->first;

    // Update currentWormId to the next worm from that client
    current_worm_id = currentClientIterator->second.advance_to_next_worm_id();
}

void TurnManager::add_player(size_t client_id, const std::list<size_t>& worm_ids_from_client) {
    if (worm_ids_from_client.empty()) {
        throw std::runtime_error("Worm id list could not be empty");
    }

    std::cout << "Added client id: " << client_id << " to the turn system with worms: ";

    // Iterate through the list of worm IDs and print each one
    for (const auto& worm_id : worm_ids_from_client) {
        std::cout << worm_id << " ";
    }

    std::cout << std::endl;

    clients_ids_to_worms_ids_iterator.emplace(client_id, worm_ids_from_client);

    //     WormIdIterator worms_id_iterator(worm_ids_from_client);
    // clients_ids_to_worms_ids_iterator[client_id] = worms_id_iterator;
}

void TurnManager::remove_worm(size_t worm_id) {
    for (auto& entry : clients_ids_to_worms_ids_iterator) {
        // Iterate every wormIdIterator until one has that worm_id and its removed from its list
        if (entry.second.remove_worm_id(worm_id)) {
            return;
        }
    }
}

void TurnManager::randomly_assign_clients_turn() {
    if (clients_ids_to_worms_ids_iterator.empty()) {
        // Handle the case when there are no clients
        return;
    }

    // Generate a random iterator to one of the keys
    auto random_iterator = std::next(std::begin(clients_ids_to_worms_ids_iterator),
                                     std::rand() % clients_ids_to_worms_ids_iterator.size());

    // Retrieve the corresponding client ID
    current_client_id = random_iterator->first;
    this->current_worm_id = random_iterator->second.getCurrentWorm();
}

bool TurnManager::is_clients_turn(size_t client_id) const {
    return client_id == current_client_id;
}

int TurnManager::get_current_client_id() const {
    if (waiting_to_start_next_turn) {
        return -1;
    } else {
        return current_client_id;
    }
}

int TurnManager::get_current_worm_id() const {
    if (waiting_to_start_next_turn) {
        return -1;
    } else {
        return current_worm_id;
    }
}

float TurnManager::get_remaining_game_time() const {
    return game_time_left; // via network we are sending float TODO test what is client receiving
}

float TurnManager::get_remaining_turn_time() const {
    return turn_time_left;
}

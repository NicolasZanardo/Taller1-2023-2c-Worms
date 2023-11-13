#include "TurnManager.h"

TurnManager::TurnManager(ClientsWorms &clientsWorms) : clientsWorms(clientsWorms) {}

void TurnManager::update(const unsigned int it) {
    if (lastUpdateTime == 0) {
        lastUpdateTime = it;
        return;
    }

    // Check if the game time has run out
    if (game_time_left <= 0) {
        return;
    }

    unsigned int elapsedTime = it - lastUpdateTime;
    lastUpdateTime = it;

    // Update times
    game_time_left -= elapsedTime;
    if (!waiting_to_start_next_turn) {
        turn_time_left -= elapsedTime;
        // Check if the turn time has run out
        if (turn_time_left <= 0) {
            end_actual_turn();
        }
    } else {
        inside_turns_time_left -= elapsedTime;
        // Check if the inside turns time has run out
        if (inside_turns_time_left <= 0) {
            advance_to_next_turn();
        }
    }

}

void TurnManager::end_actual_turn() {
    waiting_to_start_next_turn = true;
    inside_turns_time_left = inside_turns_duration;
    currentClientId = -1; // No ones turn
    currentWormId = -1; // No ones turn
}

void TurnManager::advance_to_next_turn() {
    waiting_to_start_next_turn = false;
    turn_time_left = turn_duration;

    // Find the iterator for the current client
    auto currentClientIterator = clientsWorms.find(currentClientId);

    // If the current client was not found or it was the last client, reset to the first client
    if (currentClientIterator == clientsWorms.end() || std::next(currentClientIterator) == clientsWorms.end()) {
        currentClientIterator = clientsWorms.begin();
    } else {
        // Otherwise, move to the next client
        currentClientIterator++;
    }

    // Update currentClientId
    currentClientId = currentClientIterator->first;

    // Reset to the first worm for the next client's turn
    currentWormIndex = 0;
}

bool TurnManager::isClientsTurn(size_t clientId) {
    return clientId == currentClientId;
}

size_t TurnManager::getCurrentClientId() {
    return currentClientId;
}

size_t TurnManager::getCurrentWormId() {
    return currentWormId;
}

#include "TurnManager.h"

TurnManager::TurnManager(ClientsWorms &clientsWorms): clientsWorms(clientsWorms) {}

void TurnManager::update() {
    // TODO Times and turns
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

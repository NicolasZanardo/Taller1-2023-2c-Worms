#include "GameInstance.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenarioData,
        const std::list<Client *> &clients
) :
        physicsSystem(xGravity, yGravity, scenarioData),
        instancesManager(physicsSystem, scenarioData),
        clientsWorms(),
        turnManager(clientsWorms) {
    assignWormsToClients(clients);
}

void GameInstance::update() {
    physicsSystem.update();
    turnManager.update();
    // TODO Turns, time
}

bool GameInstance::isClientsTurn(size_t id) {
    return turnManager.isClientsTurn(id);
}

GameState GameInstance::getCurrentState() {
    return GameState(
            turnManager.getCurrentClientId(), // turnManager
            1.0f, // wind physicsSystem
            120.0f, // turnManager
            15.0f// turnManager
            );
}


std::unordered_map<size_t, std::vector<Worm *>> GameInstance::getClientsWorms() {
    return clientsWorms;
}

void GameInstance::assignWormsToClients(const std::list<Client *> &clients) {

    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Iterate through each client
    for (const auto& client : clients) {
        size_t clientId = client->id;

        // Convert the unordered_map to a vector for shuffling
        std::vector<Worm*> allWorms;
        for (const auto& entry : instancesManager.getWorms()) {
            allWorms.push_back(entry.second);
        }

        // Shuffle the worms randomly
        std::shuffle(allWorms.begin(), allWorms.end(), std::default_random_engine(std::rand()));

        // Assign a subset of worms to the client
        // For simplicity, let's say each client gets half of the worms
        size_t numWormsToAssign = allWorms.size() / 2;
        std::vector<Worm*> assignedSubset(allWorms.begin(), allWorms.begin() + numWormsToAssign);

        // Store the assigned worms for the client in the map
        clientsWorms[clientId] = std::move(assignedSubset);
    }
}


// Actions
void GameInstance::startMovingCurrentWormLeft() {
    auto worm = instancesManager.getWorm(turnManager.getCurrentWormId());
    worm->startMovingLeft();
}

void GameInstance::startMovingCurrentWormRight() {
    auto worm = instancesManager.getWorm(turnManager.getCurrentWormId());
    worm->startMovingRight();
}
void GameInstance::stopMovingCurrentWorm() {
    auto worm = instancesManager.getWorm(turnManager.getCurrentWormId());
    worm->stopMoving();
}
void GameInstance::jumpBackCurrentWorm() {
    auto worm = instancesManager.getWorm(turnManager.getCurrentWormId());
    worm->jumpBackwards();
}
void GameInstance::jumpForwardCurrentWorm() {
    auto worm = instancesManager.getWorm(turnManager.getCurrentWormId());
    worm->jumpForward();
}

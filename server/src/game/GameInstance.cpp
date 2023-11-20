#include "GameInstance.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenarioData,
        const std::list<Client *> &clients,
        int rate
) :
        physicsSystem(rate, xGravity, yGravity, scenarioData),
        instancesManager(physicsSystem, scenarioData),
        clientsWorms(),
        turnManager(rate) {
    assign_worms_to_clients(clients);
    turnManager.randomly_assign_clients_turn();
}

// TODO DELETE
std::string get_name(MovementStateDto state) {
    switch (state) {
        case MovementStateDto::idle:
            return "idle";
        case MovementStateDto::moving:
            return "moving";
        case MovementStateDto::going_upwards:
            return "going_upwards";
        case MovementStateDto::falling:
            return "falling";
        default:
            return "unknown"; // Handle unknown enum values
    }
}

void GameInstance::update(const int it) {
    auto worms = instancesManager.getWorms();
    int current_worm_id = turnManager.get_current_worm_id();
    std::shared_ptr<Worm> active_worm = nullptr;
    if (current_worm_id != -1) {
        active_worm = instancesManager.getWorm(current_worm_id);
    }
    physicsSystem.update(worms);
    turnManager.update(it, worms, active_worm);
}

bool GameInstance::isClientsTurn(size_t id) {
    return turnManager.is_clients_turn(id);
}

GameState GameInstance::getCurrentState() {
    return GameState(
            turnManager.get_current_client_id(),
            turnManager.get_current_worm_id(), // turnManager
            1.0f, // wind physicsSystem
            turnManager.get_remaining_game_time(), // turnManager
            turnManager.get_remaining_turn_time()// turnManager
    );
}

ClientsWorms GameInstance::getClientsWorms() {
    return clientsWorms;
}

void GameInstance::assign_worms_to_clients(const std::list<Client *> &clients) {
    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Convert the unordered_map to a vector for shuffling
    std::vector<std::shared_ptr<Worm>> allWorms;
    for (const auto &[_, worm]: instancesManager.getWorms()) {
        allWorms.push_back(worm);
    }

    // Shuffle the worms randomly
    std::shuffle(allWorms.begin(), allWorms.end(), std::default_random_engine(std::rand()));

    // Calculate the number of worms per player
    size_t totalWorms = allWorms.size();
    size_t numPlayers = clients.size();
    size_t wormsPerPlayer = totalWorms / numPlayers;
    size_t extraWorms = totalWorms % numPlayers; // Extra worms for players with fewer worms

    // Iterate through each client
    for (const auto &client: clients) {
        size_t clientId = client->id;

        // Assign worms to the client
        size_t numWormsToAssign = wormsPerPlayer + (extraWorms > 0 ? 1 : 0);
        std::vector<std::shared_ptr<Worm>> assignedSubset(allWorms.begin(), allWorms.begin() + numWormsToAssign);

        // Adjust health for worms of players with fewer worms
        if (extraWorms > 0) {
            for (auto &worm: assignedSubset) {
                worm->health += 25; // Add 25 points of health
            }
            --extraWorms;
        }

        // Remove assigned worms from the pool
        allWorms.erase(allWorms.begin(), allWorms.begin() + numWormsToAssign);


        // add client with its wormds ids to the TurnManager
        std::list<size_t> wormIds;
        for (const auto &worm : assignedSubset) {
            wormIds.push_back(worm->id);
        }
        turnManager.add_player(clientId, wormIds);

        // assign Worm* to clients ids
        clientsWorms[clientId] = std::move(assignedSubset);
    }
}


// Actions
void GameInstance::startMovingCurrentWormLeft() {
    auto worm_id = turnManager.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instancesManager.getWorm(worm_id);
        worm->startMovingLeft();
    }
}

void GameInstance::startMovingCurrentWormRight() {
    auto worm_id = turnManager.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instancesManager.getWorm(worm_id);
        worm->startMovingRight();
    }
}

void GameInstance::stopMovingCurrentWorm() {
    auto worm_id = turnManager.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instancesManager.getWorm(worm_id);
        worm->stopMoving();
    }
}

void GameInstance::jumpBackCurrentWorm() {
    auto worm_id = turnManager.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instancesManager.getWorm(worm_id);
        worm->jumpBackwards();
    }
}

void GameInstance::jumpForwardCurrentWorm() {
    auto worm_id = turnManager.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instancesManager.getWorm(worm_id);
        worm->jumpForward();
    }
}

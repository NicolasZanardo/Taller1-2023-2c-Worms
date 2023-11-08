#include "GameInstance.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenario, // TODO Game config struct
        const std::list<Client*>& clients
):  physicsSystem(xGravity, yGravity, scenario),
    entityManager(physicsSystem),
    clientWormsMap(),
    gameQueue(50) {
    init_game(scenario, clients);
}

void GameInstance::run() {
    // TODO LOOP
    // _process_actions();
    // _apply_physics()
    // _update_game() Turn, time, etc
    // _maintain_connections
    // _send_game_state()
    // _synchronize()
}

void GameInstance::stop() {
 // TODO Clients back to WaitingLobby
}

/* PRIVATE */

void GameInstance::init_game(const GameScenarioData &scenario, const std::list<Client *>& clients) {
    _create_and_assign_worms(scenario, clients);
    // TODO Send to clients INITIAL MESSAGE (Beam Positions, etc)
    // TODO Send first update()
}

void GameInstance::_process_actions() {
    /* NetMessage* msg = nullptr;
    while ((msg = gameQueue.pop())) {
        try {
            msg->exec(game);
        } catch () {

        }
        delete msg;
    } */
}

void GameInstance::_create_and_assign_worms(const GameScenarioData &scenario, const std::list<Client *>& clients) {
    // Calculate the number of clients and the total number of worms
    size_t numClients = clients.size();
    size_t numWorms = scenario.worms.size();

    // Calculate the base number of worms per client
    size_t wormsPerClient = numWorms / numClients;

    // Calculate the number of clients that will have an extra worm
    size_t clientsWithExtraWorm = numWorms % numClients;

    // Create a list of available worms
    std::list<int> availableWorms;
    for (int i = 0; i < numWorms; i++) {
        availableWorms.push_back(i);
    }

    // Assign worms to clients
    for (Client* client : clients) {
        size_t wormsToAssign = wormsPerClient;

        // Check if this client should have an extra worm
        if (clientsWithExtraWorm > 0) {
            wormsToAssign++;
            clientsWithExtraWorm--;
        }

        std::list<size_t> assignedWorms;
        for (int i = 0; i < wormsToAssign; i++) {
            if (!availableWorms.empty()) {
                size_t wormId = availableWorms.front();
                availableWorms.pop_front();
                WormScenarioData wormScenarioData = scenario.worms[wormsToAssign];
                entityManager.create_worm(wormScenarioData); // TODO Test out of index
                assignedWorms.push_back(wormId);
            }
        }

        clientWormsMap[client->id] = assignedWorms;
    }

    // Adjust the health of worms owned by clients with less worms
    int extraHealth = 25;

    // Iterates thorught the clients lists of worms
    // If a client has a worm list with less worms than the normal adapt health for all worms in the list
    for (const auto& entry : clientWormsMap) {
        size_t clientWormCount = entry.second.size();
        if (clientWormCount < wormsPerClient) {
            for (size_t wormId : entry.second) {
                // Increase the health of worms owned by this client
                Worm* worm = entityManager.get_worm(wormId);
                if (worm) {
                    worm->health += extraHealth;
                }
            }
        }
    }
}



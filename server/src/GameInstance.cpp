#include "GameInstance.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenario, // TODO Game config struct
        const std::list<Client*>& clients
): physicsSystem(xGravity, yGravity, scenario),
   instancesManager(physicsSystem),
   clientWormsMap(),
   gameQueue(50) {
    init_game(scenario, clients);
}

void GameInstance::run() {
    // TODO LOOP
    _process_actions();
    _apply_physics();
    // _update_game() Turn, time, etc
    // _maintain_connections
    _broadcast_updated_game_state();
    // _synchronize()
}

void GameInstance::stop() {
 // TODO Clients back to WaitingLobby
}

/* PRIVATE */

// Init methods
void GameInstance::init_game(const GameScenarioData &scenario, const std::list<Client *>& clients) {
    _create_and_assign_worms(scenario, clients);
    _broadcast_initial_game_state(scenario);
    _broadcast_updated_game_state();
}

void GameInstance::_create_and_assign_worms(const GameScenarioData &scenario, const std::list<Client *>& clients) {

    size_t numClients = clients.size();
    size_t numWorms = scenario.worms.size();
    size_t wormsPerClient = numWorms / numClients;
    size_t extraWorms = numWorms % numClients;

    int extraHealth = 25;

    // Assign worms to clients
    auto wormIter = scenario.worms.begin();
    for (Client* client : clients) {
        size_t wormsToAssign = wormsPerClient + (extraWorms-- > 0 ? 1 : 0);
        std::list<Worm*> assignedWorms;

        for (size_t i = 0; i < wormsToAssign && wormIter != scenario.worms.end(); ++i) {
            WormScenarioData wormScenarioData = *wormIter;
            Worm* worm = instancesManager.create_worm(wormScenarioData);

            if (worm) {
                assignedWorms.push_back(worm);
            }

            ++wormIter;
        }

        // Update the assigned worms in clientWormsMap
        clientWormsMap[client] = assignedWorms;
    }

    // Adjust the health for clients with fewer worms
    for (const auto& entry : clientWormsMap) {
        size_t clientWormCount = entry.second.size();
        if (clientWormCount < wormsPerClient) {
            for (Worm* worm : entry.second) {
                // Increase the health of all worms owned by this client
                worm->health += extraHealth;
            }
        }
    }
}

void GameInstance::_broadcast_initial_game_state(const GameScenarioData &scenario) {

    for (auto beamScenarioData: scenario.beams) {

    }

    // Iterate and send it to every client
    for (const auto& clientWormsPair: clientWormsMap) {
        clientWormsPair.first->communicate(new NetMessageChat());
    }

}

void GameInstance::_broadcast_updated_game_state() {

    // Iterate every client worm populating the UpdateStateMessage
    for (const auto& clientWormsPair: clientWormsMap) {

    }

    // TODO iterate the rest of instances in the map (Projectiles and supply boxes)

    // Iterate and send the generated UpdateStateMessage to every Client
    for (const auto& clientWormsPair: clientWormsMap) {

    }
}


// Loop methods
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

void GameInstance::_apply_physics() {
    physicsSystem.update();
}






#include "GameInstance.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenario, // TODO Game config struct
        const std::list<Client*>& clients
): physicsSystem(xGravity, yGravity, scenario),
   instancesManager(physicsSystem),
   clientWormsMap(),
   gameQueue(100),
   netMessageBehaviour() {
    init_game(scenario, clients);
}

void GameInstance::run() {
    // TODO LOOP
    _process_actions();
    _apply_physics();
    // _update_game() Turn, time, etc
    // _maintain_connections
    _broadcast_game_state_update();
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
    _broadcast_game_state_update();
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
    auto initialStateMessage = std::make_unique<NetMessageInitialGameState>(
            scenario.room_width,
            scenario.room_height,
            scenario.beams
    );

    // Iterate and send it to every client
    for (const auto& [client, _] : clientWormsMap) {
        client->communicate(initialStateMessage.get());
    }
}

void GameInstance::_broadcast_game_state_update() {

    auto gameStateUpdateMessage = std::make_unique<NetMessageGameStateUpdate>(
        1, // Active entity
        1.0f, // Wind speed
        240.f, // remaining game time
        15.0f // remaining turn time
    ); // TODO Hardcoded for now

    for (const auto& [client, worms] : clientWormsMap) {
        for(const auto worm: worms) {
            const WormDto& wormDto = worm->toWormDto(client->id);
            gameStateUpdateMessage->add(wormDto);
        }
    }

    // TODO ALSO ADD(&BulletDtos)
    // TODO ALSO ADD(&EventDtos)

    for (const auto& [client, _] : clientWormsMap) {
        client->communicate(gameStateUpdateMessage.get());
    }
}


// Loop methods
void GameInstance::_process_actions() {
    NetMessage* msg = nullptr;
    while ((msg = gameQueue.pop())) {
        try {
            // TODO IF (msg is from active_client)
            msg->execute(netMessageBehaviour);
        } catch (const std::exception& ex) {
            // TODO
        }
        delete msg;
    }
}

void GameInstance::_apply_physics() {
    physicsSystem.update();
}






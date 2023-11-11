#include "GameEngineInstance.h"

GameEngineInstance::GameEngineInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenario, // TODO Game config struct
        const std::list<Client *> &clients
) : gameClients(clients),
    game(xGravity, yGravity, scenario, clients),
    gameQueue(100),
    netMessageBehaviour(gameClients, game) {
    initial_broadcast(scenario);
}

void GameEngineInstance::run() {
    _process_actions();
    game.update();
    // _maintain_connections();
    _broadcast_game_state_update();
    // _synchronize()
}

void GameEngineInstance::stop() {
    // TODO Clients back to WaitingLobbyx
}

/* PRIVATE */
void GameEngineInstance::initial_broadcast(const GameScenarioData &scenario) {
    _broadcast_initial_game_state(scenario);
    _broadcast_game_state_update();
}


void GameEngineInstance::_broadcast_initial_game_state(const GameScenarioData &scenario) {
    // map BeamScenarioData to BeamDto
    std::vector<BeamDto> beamDtos;
    beamDtos.reserve(scenario.beams.size());
    std::transform(scenario.beams.begin(), scenario.beams.end(), std::back_inserter(beamDtos),
                   [](const BeamScenarioData& beamScenarioData) {
                       return beamScenarioData.toBeamDto();
                   }
    );

    auto initialStateMessage = new NetMessageInitialGameState(
            scenario.room_width,
            scenario.room_height,
            beamDtos
    );
    gameClients.sendAll(initialStateMessage);
    delete initialStateMessage;
}

void GameEngineInstance::_broadcast_game_state_update() {
    auto gameState = game.getCurrentState();
    auto gameStateUpdateMessage = new NetMessageGameStateUpdate(
            gameState.currentTurnClientId, // pass directly the game state?
            gameState.windSpeed,
            gameState.remainingGameTime,
            gameState.remainingGameTime
    );

    for (const auto &[clientId, worms]: game.getClientsWorms()) {
        for (const auto worm: worms) {
            const WormDto &wormDto = worm->toWormDto(clientId);
            gameStateUpdateMessage->add(wormDto);
        }
    }

    // TODO ALSO ADD(&BulletDtos)
    // TODO ALSO ADD(&EventDtos)

    gameClients.sendAll(gameStateUpdateMessage);
    delete gameStateUpdateMessage;
}


// Loop methods
void GameEngineInstance::_process_actions() {
    NetMessage *msg = nullptr;
    while (gameQueue.try_pop(msg)) {
        try {
            auto *action = dynamic_cast<NetMessageGameAction *>(msg);
            if (action != nullptr && game.isClientsTurn(action->client_id)) {
                action->execute(netMessageBehaviour);
            }
        } catch (const std::exception &ex) {
            // TODO
        }
        delete msg;
    }

}

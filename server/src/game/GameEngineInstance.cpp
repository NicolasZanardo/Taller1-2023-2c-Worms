#include "GameEngineInstance.h"

GameEngineInstance::GameEngineInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenario, // TODO Game config struct
        const std::list<Client *> &clients
) : gameClients(clients),
    game(xGravity, yGravity, scenario, clients),
    gameQueue(100),
    netMessageBehaviour(gameClients, game),
    rate(30),
    keep_executing(true) {
    initial_broadcast(scenario);
}

void GameEngineInstance::run() {

    // Variables para controlar el frame-rate
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0, behind = 0, lost = 0;
    int it = 1;

    // Loop principal
    while (keep_executing) {
        _process_actions();
        game.update(it);
        // _maintain_connections();
        _broadcast_game_state_update();
        // _synchronize()

        // https://eldipa.github.io/book-of-gehn/articles/2019/10/23/Constant-Rate-Loop.html
        // Drop n rest
        it = 0;
        t2 = std::chrono::steady_clock::now();
        diff = t2 - t1;
        rest = rate - std::ceil(diff.count());

        if (rest < 0) {
            fprintf(stderr, ">> Ciclo principal: pérdida de frame/s.\n");
            behind = -rest;
            // lost = rate + (behind - behind % rate);
            rest = rate - behind % rate;
            lost = behind + rest;
            t1 += std::chrono::milliseconds(lost);
            it += std::floor(lost / rate);
        }

        // fprintf(stderr, "ENGINE: Sleeping for %i ms.\n", rest);

        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }


    // Terminamos las conexiones
    // TODO game clients to lobby?
    // gameQueue.close() ? or is it maneged by server
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
    //map BeamScenarioData to BeamDto
    auto message = new NetMessageInitialGameState(
        scenario.room_width,
        scenario.room_height
    );

    for (auto item : scenario.beams) {
        message->add(item.toBeamDto());
    }

    gameClients.sendAll(std::shared_ptr<NetMessage>(message));
}

void GameEngineInstance::_broadcast_game_state_update() {
    auto gameState = game.getCurrentState();
    auto gameStateUpdateMessage = new NetMessageGameStateUpdate(
            gameState.currentTurnClientId, // pass directly the game state?
            gameState.windSpeed,
            gameState.remainingGameTime,
            gameState.remainingTurnTime
    );

    for (const auto &[clientId, worms]: game.getClientsWorms()) {
        for (const auto worm: worms) {
            const WormDto &wormDto = worm->toWormDto(clientId);
            gameStateUpdateMessage->add(wormDto);
        }
    }

    // TODO ALSO ADD(&BulletDtos)
    // TODO ALSO ADD(&EventDtos)

    gameClients.sendAll(std::shared_ptr<NetMessage>(gameStateUpdateMessage));
}


// Loop methods
void GameEngineInstance::_process_actions() {
    std::shared_ptr<NetMessage> msg = nullptr;
    while (gameQueue.try_pop(msg)) {
        msg->execute(netMessageBehaviour);
    }
}

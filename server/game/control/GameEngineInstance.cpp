#include "GameEngineInstance.h"

GameEngineInstance::GameEngineInstance(
    float xGravity,
    float yGravity,
    const GameScenarioData &scenario,
    const std::list<Client *> &clients
) : rate(60),
    game_clients(clients),
    game(xGravity, yGravity, scenario, clients, rate),
    game_queue(1000),
    net_message_behaviour(game_clients, game),
    keep_executing(true) {
    switch_clients_game_queue(clients);
    initial_broadcast(scenario);
}

void GameEngineInstance::run() {
    auto t1 = std::chrono::steady_clock::now();
    auto t2 = t1;
    std::chrono::duration<float, std::milli> diff;
    int rest = 0, behind = 0, lost = 0;
    int it = 1;

    while (keep_executing) {
        process_actions();
        if (game.update(it)) {
            keep_executing = false;
            break;
        }
        // _maintain_connections();
        broadcast_game_state_update();
        // _synchronize()

        // https://eldipa.github.io/book-of-gehn/articles/2019/10/23/Constant-Rate-Loop.html
        // Drop n rest
        it = 0;
        t2 = std::chrono::steady_clock::now();
        diff = t2 - t1;
        rest = rate - std::ceil(diff.count());

        if (rest < 0) {
            // fprintf(stderr, ">> Ciclo principal: pérdida de frame/s.\n");
            behind = -rest;
            // lost = rate + (behind - behind % rate);
            rest = rate - behind % rate;
            lost = behind + rest;
            t1 += std::chrono::milliseconds(lost);
            it += std::floor(lost / rate);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(rest));
        t1 += std::chrono::milliseconds(rate);
        it += 1;
    }

    broadcast_game_ended();
    // TODO clients back to lobby?
    // game_queue.close();
}

void GameEngineInstance::stop() {
    // TODO Clients back to WaitingLobbyx
}

void GameEngineInstance::process_actions() {
    std::shared_ptr<NetMessage> msg = nullptr;
    while (game_queue.try_pop(msg)) {
        msg->execute(net_message_behaviour);
    }
}

void GameEngineInstance::switch_clients_game_queue(std::list<Client *> clients) {
    for (auto client: clients) {
        client->switch_lobby(&game_queue);
    }
}


// Broadcasts

void GameEngineInstance::initial_broadcast(const GameScenarioData &scenario) {
    broadcast_initial_game_state(scenario);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    broadcast_game_state_update();
}


void GameEngineInstance::broadcast_initial_game_state(const GameScenarioData &scenario) {
    auto message = new NetMessageInitialGameState(
        scenario.room_width,
        scenario.room_height,
        scenario.water_height_level
    );

    for (auto item: scenario.beams) {
        message->add(item.toBeamDto());
        std::cout << "BeamDto x: " << item.toBeamDto().x << " y: " << item.toBeamDto().y << std::endl;
    }

    for (const auto &[clientId, worms]: game.get_clients_worms()) {
        for (const auto &wrm: worms) {
            std::cout << "Init Worm id: " << wrm->toWormDto(clientId).entity_id
                      << " with client id: " << wrm->toWormDto(clientId).client_id << std::endl;
            message->add(wrm->toWormDto(clientId));
        }
    }

    game_clients.send_all(message->share());
}

void GameEngineInstance::broadcast_game_state_update() {
    GameState state = game.get_current_state();
    auto msg = new NetMessageGameStateUpdate(
        state.current_turn_client_id,
        state.current_turn_worm_id,
        state.focused_entity_id,
        state.wind_speed,
        state.remaining_game_time,
        state.remaining_turn_time
        );

    for (const auto &[client_id, worms]: game.get_clients_worms()) {
        for (const auto& worm: worms) {
            msg->add(worm->toWormDto(client_id));
        }
    }

    for (const auto &projectile : game.get_projectiles()) {
        msg->add(projectile->to_dto());
    }

    // TODO ALSO ADD(&EventDtos)

    game_clients.send_all(msg->share());
}

void GameEngineInstance::broadcast_game_ended() {
    auto end_game_message = new NetMessageGameEnded(game.get_winner_client_id());
    game_clients.send_all(end_game_message->share());
}

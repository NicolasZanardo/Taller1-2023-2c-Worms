#ifndef SERVER_GAME_ENGINE_INSTANCE_H
#define SERVER_GAME_ENGINE_INSTANCE_H

#include <list>
#include <unordered_map>
#include <atomic>
#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#include "GameInstance.h"
#include "networking.h"
#include "thread.h"
#include "GameScenarioData.h"
#include "client.h"
#include "GameNetMessageBehaviour.h"
#include "InGameClients.h"


class GameEngineInstance : public Thread {
private:
    int rate;
    InGameClients game_clients;
    GameInstance game;
    NetQueue game_queue;
    GameNetMessageBehaviour net_message_behaviour;
    std::atomic_bool keep_executing;

    // Init methods
    void switch_clients_game_queue(std::list<Client *> clients);
    void initial_broadcast(const GameScenarioData &scenario, const std::vector<int>& order);
    void start_game_();
    void process_actions();

    void broadcast_initial_game_state(const GameScenarioData &scenario, const std::vector<int>& order);
    void broadcast_game_state_update();
    void broadcast_game_ended();

public:
    GameEngineInstance(
            float xGravity,
            float yGravity,
            const GameScenarioData &scenario,
            const std::list<Client *> &clients
            );

    void run() override;

    void stop() override;

};


#endif

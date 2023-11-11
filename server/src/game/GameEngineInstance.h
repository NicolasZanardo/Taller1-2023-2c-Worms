#ifndef SERVER_GAME_ENGINE_INSTANCE_H
#define SERVER_GAME_ENGINE_INSTANCE_H

#include <list>
#include <unordered_map>
#include "GameInstance.h"
#include "../../../common_base/Networking/Messages/net_queue.h"
#include "../../../common_base/networking.h"
#include "../../../common_base/thread.h"
#include "scenario/GameScenarioData.h"
#include "../client/client.h"
#include "GameNetMessageBehaviour.h"
#include "InGameClients.h"


class GameEngineInstance: public Thread {
private:
    InGameClients gameClients;
    GameInstance game;
    NetQueue gameQueue;
    GameNetMessageBehaviour netMessageBehaviour;

    // Init methods
    void initial_broadcast(const GameScenarioData& scenario);
    void _broadcast_initial_game_state(const GameScenarioData &scenario);

    // Loop methods
    void _process_actions();
    void _broadcast_game_state_update();


public:
    explicit GameEngineInstance(float xGravity, float yGravity, const GameScenarioData& scenario, const std::list<Client*>& clients);
    void run() override;
    void stop() override;

};


#endif

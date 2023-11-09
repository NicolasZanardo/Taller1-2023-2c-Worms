#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

#include <list>
#include <unordered_map>
#include "../../common_base/Networking/Messages/net_queue.h"
#include "../../common_base/networking.h"
#include "../../common_base/thread.h"
#include "simulation/PhysicsSystem.h"
#include "client/client.h"
#include "model/instances/Worm.h"
#include "model/instances/InstancesManager.h"

typedef std::unordered_map<Client*, std::list<Worm *>> ClientWormsMap;

class GameInstance: public Thread {
private:
    PhysicsSystem physicsSystem;
    InstancesManager instancesManager;
    ClientWormsMap clientWormsMap;
    NetQueue gameQueue;

    // Init methods
    void init_game(const GameScenarioData& scenario, const std::list<Client*>& clients);
    void _create_and_assign_worms(const GameScenarioData &scenario, const std::list<Client *>& clients);
    void _broadcast_initial_game_state(const GameScenarioData &scenario);
    void _broadcast_game_state_update();

    // Loop methods
    void _process_actions();
    void _apply_physics();


public:
    explicit GameInstance(float xGravity, float yGravity, const GameScenarioData& scenario, const std::list<Client*>& clients);
    void run() override;
    void stop() override;

};


#endif

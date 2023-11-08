#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

#include <list>
#include <unordered_map>
#include "../../common_base/Networking/Messages/net_queue.h"
#include "../../common_base/thread.h"
#include "simulation/PhysicsSystem.h"
#include "client/client.h"
#include "model/entities/Worm.h"
#include "model/entities/EntityManager.h"

typedef std::unordered_map<int, std::list<size_t>> ClientWormsMap;

class GameInstance: public Thread {
private:
    PhysicsSystem physicsSystem;
    EntityManager entityManager;
    ClientWormsMap clientWormsMap;
    NetQueue gameQueue;

    void init_game(const GameScenarioData& scenario, const std::list<Client*>& clients);
    void _create_and_assign_worms(const GameScenarioData &scenario, const std::list<Client *>& clients);
    void _process_actions();

public:
    explicit GameInstance(float xGravity, float yGravity, const GameScenarioData& scenario, const std::list<Client*>& clients);
    void run() override;
    void stop() override;

};


#endif

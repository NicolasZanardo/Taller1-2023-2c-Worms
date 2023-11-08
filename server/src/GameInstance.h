#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

#include <list>
#include <unordered_map>
#include "../../common_base/Networking/Messages/net_queue.h"
#include "simulation/PhysicsSystem.h"

typedef std::unordered_map<int, std::list<int>> ClientWormsMap;

class GameInstance {
private:
    ClientWormsMap clientWormsMap;
    NetQueue gameQueue;
    PhysicsSystem physicsSystem;

public:
    explicit GameInstance(const GameScenario& scenario);

};


#endif

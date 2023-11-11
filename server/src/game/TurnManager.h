#ifndef SERVER_TURNMANAGER_H
#define SERVER_TURNMANAGER_H

#include <cstdio>
#include <unordered_map>
#include "model/instances/Worm.h"


typedef std::unordered_map<size_t, std::vector<Worm *>> ClientsWorms;

class TurnManager {
    ClientsWorms& clientsWorms;
    size_t currentClientId = 1;
    size_t currentWormId = 1;

public:
    TurnManager(ClientsWorms& clientsWorms);
    void update();
    bool isClientsTurn(size_t clientId);
    size_t getCurrentClientId();
    size_t getCurrentWormId();
};


#endif

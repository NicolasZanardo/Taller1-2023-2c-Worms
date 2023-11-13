#ifndef SERVER_TURNMANAGER_H
#define SERVER_TURNMANAGER_H

#include <vector>
#include <cstdio>
#include <unordered_map>
#include "model/instances/Worm.h"

typedef std::unordered_map<size_t, std::vector<Worm *>> ClientsWorms;

class TurnManager {
    ClientsWorms& clientsWorms;
    size_t currentClientId = 1;
    size_t currentWormId = 1;
    unsigned int game_time_left;

    unsigned int turn_time_left;
    const unsigned int turn_duration = 60;

    unsigned int inside_turns_time_left;
    const unsigned int inside_turns_duration = 3;

    unsigned int lastUpdateTime;
    bool waiting_to_start_next_turn;

public:
    TurnManager(ClientsWorms& clientsWorms);

    bool isClientsTurn(size_t clientId);
    size_t getCurrentClientId();
    size_t getCurrentWormId();

    void update(unsigned int it);
    void end_actual_turn();
    void advance_to_next_turn();

};


#endif

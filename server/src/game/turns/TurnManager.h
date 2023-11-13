#ifndef SERVER_TURNMANAGER_H
#define SERVER_TURNMANAGER_H

#include <vector>
#include <list>
#include <cstdio>
#include <unordered_map>
#include "WormIdIterator.h"

typedef std::unordered_map<size_t, WormIdIterator> ClientsIdsToWormsIdsIterator;

class TurnManager {
    ClientsIdsToWormsIdsIterator clients_ids_to_worms_ids_iterator;
    size_t current_client_id;
    size_t current_worm_id;

    float game_time_left = 6000;// 1080000; // millis

    float turn_time_left = 600;// 60000;
    const float turn_duration = 600;// 60000; // millis

    float inside_turns_time_left = 200; // 3000;
    const float inside_turns_duration = 200; // 3000; // millis

    bool waiting_to_start_next_turn = false;

public:
    TurnManager();

    size_t get_current_client_id() const;
    size_t get_current_worm_id() const;
    float get_remaining_game_time() const;
    float get_remaining_turn_time() const;

    void add_player(size_t client_id, const std::list<size_t>& worm_ids_from_client);
    void remove_worm(size_t worm_id);
    void randomly_assign_clients_turn();

    bool is_clients_turn(size_t client_id) const;


    void update(const float diff);
    void end_actual_turn();
    void advance_to_next_turn();


};


#endif

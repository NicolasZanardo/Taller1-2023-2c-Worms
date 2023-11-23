#ifndef SERVER_TURNMANAGER_H
#define SERVER_TURNMANAGER_H

#include <vector>
#include <list>
#include <cstdio>
#include <unordered_map>
#include "WormIdIterator.h"
#include "../../model/worm/Worm.h"

typedef std::unordered_map<size_t, WormIdIterator> ClientsIdsToWormsIdsIterator;

class TurnManager {
    int rate;
    ClientsIdsToWormsIdsIterator clients_ids_to_worms_ids_iterator;
    size_t current_client_id;
    size_t current_worm_id;

    int game_time_left = 60000; // millis

    int turn_time_left = 10000; // 60000;
    const int turn_duration = 10000; // 60000;

    bool waiting_to_start_next_turn = false;

    bool worms_are_still(std::unordered_map<size_t, std::shared_ptr<Worm>>& worms);

public:
    TurnManager(const int rate);

    int get_current_client_id() const;
    int get_current_worm_id() const;
    float get_remaining_game_time() const;
    float get_remaining_turn_time() const;

    void add_player(size_t client_id, const std::list<size_t>& worm_ids_from_client);
    void remove_worm(size_t worm_id);
    void randomly_assign_clients_turn();

    bool is_clients_turn(size_t client_id) const;


    void update(
            const int it,
            std::unordered_map<size_t, std::shared_ptr<Worm>>& worms,
            const std::shared_ptr<Worm>& active_worm
            );
    void end_actual_turn(const std::shared_ptr<Worm>& active_worm);
    void advance_to_next_turn();


};


#endif
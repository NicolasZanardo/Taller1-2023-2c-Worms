#ifndef SERVER_TURNMANAGER_H
#define SERVER_TURNMANAGER_H

#include <vector>
#include <list>
#include <cstdio>
#include <unordered_map>
#include "WormIdIterator.h"
#include "Worm.h"
#include "Projectile.h"
#include "TurnSystemCfg.h"

typedef std::unordered_map<size_t, WormIdIterator> ClientsIdsToWormsIdsIterator;

enum class TurnState {
    TURN_TIME,
    ADDITIONAL_TURN_TIME,
    WAITING_TO_START_NEXT_TURN
};


class TurnSystem {
    const int TURN_DURATION;
    const int MATCH_DURATION;
    const int TIME_AFTER_ENDING_TURN_ACTION;

    TurnState state;
    int rate;
    ClientsIdsToWormsIdsIterator clients_ids_to_worms_ids_iterator;
    int current_client_id;
    int current_worm_id;

    int game_time_left = MATCH_DURATION;
    int turn_time_left = TURN_DURATION;

    bool worms_are_still(std::unordered_map<int, std::shared_ptr<Worm>>& worms);

public:
    TurnSystem(int rate, TurnSystemCfg &cfg);

    int get_current_client_id() const;
    int get_current_worm_id() const;
    int get_remaining_game_time() const;
    int get_remaining_turn_time() const;

    void add_player(int client_id, const std::list<int>& worm_ids_from_client);
    void remove_worm(int worm_id);
    void randomly_assign_clients_turn();

    bool is_clients_turn(int client_id) const;


    void update(
            const int it,
            std::unordered_map<int, std::shared_ptr<Worm>>& worms,
            const std::shared_ptr<Worm>& active_worm,
            const std::vector<std::shared_ptr<Projectile>> &projectiles
            );
    void end_actual_turn(const std::shared_ptr<Worm>& active_worm);
    void advance_to_next_turn();
    void check_ending_turn_action(const std::shared_ptr<Worm>& active_worm);
    bool step_turn_time(const int it, const std::shared_ptr<Worm>& active_worm);
    std::vector<int> get_order();

};


#endif

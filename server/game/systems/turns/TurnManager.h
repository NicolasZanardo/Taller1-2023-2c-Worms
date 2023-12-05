#ifndef SERVER_TURNMANAGER_H_
#define SERVER_TURNMANAGER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "roulete.h"
#include "Projectile.h"
#include "Worm.h"
#include "ClientTurn.h"
#include <iostream>

enum class TurnState {
    TURN_TIME,
    POST_ACTION_TIME,
    WAITING_TO_START_NEXT_TURN
};

class TurnManager {
    TurnState state;
    std::vector<std::shared_ptr<Projectile>>& projectiles;
    std::unordered_map<int, std::shared_ptr<Worm>>& worms;

    std::vector<ClientTurn*> clients_turns;
    int current_client_idx = 0;

    int turn_length;
    int turn_remaining_time;
    int game_remaining_time;
    int post_action_time;
    int time_rate;

    void next_turn();
    void step_turn_time(int it);
    bool worms_are_still();

    public:
    ~TurnManager();
    TurnManager(
        std::vector<std::shared_ptr<Projectile>>& projectiles,
        std::unordered_map<int, std::shared_ptr<Worm>>& worms,
        int game_time, int turn_length, int post_action_time,
        int time_rate
    );

    int current_client();
    std::shared_ptr<Worm> get_current_worm();
    int get_current_worm_id();
    void add_player(int client, const std::shared_ptr<Worm>& worm);
    bool game_has_ended() const;
    int get_game_remaining_time() const;
    int get_turn_remaining_time() const;

    void remove(int entity_id);
    void update(int delta_time);

    std::vector<int> get_order();
};
#endif
#ifndef SERVER_TURNMANAGER_H_
#define SERVER_TURNMANAGER_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include "roulete.h"
#include "Projectile.h"
#include "Worm.h"

class ClientTurn {
    public: 
    int client_id;
    Roulete<std::shared_ptr<Worm>> entities;

    explicit ClientTurn(int client_id) :
    client_id(client_id) { }
};

class TurnManager {
    std::vector<std::shared_ptr<Projectile>>& projectiles;
    std::unordered_map<int, std::shared_ptr<Worm>>& worms;
    int turn_lenght;
    int turn_remaining_time;
    int game_remaining_time;
    int post_action_time;
    int time_rate;
    bool on_overtime;
    void remove_dead_worms();

    public:
    ~TurnManager();
    TurnManager(
        std::vector<std::shared_ptr<Projectile>>& projectiles,
        std::unordered_map<int, std::shared_ptr<Worm>>& worms,
        int game_time, int turn_lenght, int post_action_time,
        int time_rate
    );
    Roulete<ClientTurn*> clients;
    void next_turn();

    int current_client();
    std::shared_ptr<Worm> current_entity();
    void add_player(int client, std::shared_ptr<Worm> worm);
    bool game_has_ended();
    int get_game_remaining_time();
    int get_turn_remaining_time();

    void remove(int entity_id);
    void update(int delta_time);
};
#endif
#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <list>
#include <vector>
#include <algorithm> // Include for std::random_shuffle
#include <cstdlib>   // Include for std::srand and std::rand
#include <random>
#include <ctime>     // Include for std::time
#include "../model/worm/Worm.h"
#include "../core/InstancesManager.h"
// #include "../../client/client.h"
#include "../systems/physics/PhysicsSystem.h"
#include "../systems/turns/TurnSystem.h"
#include "../systems/updatables/UpdatablesSystem.h"
#include "../systems/shot/ShotSystem.h"

class Client;

typedef std::unordered_map<size_t, std::vector<std::shared_ptr<Worm>>> ClientsWorms;

struct GameState {
    size_t current_client_id;
    size_t current_worm_id;
    float windSpeed;
    float remainingGameTime;
    float remainingTurnTime;

    GameState(
            size_t currentTurnClientId,
            size_t current_worm_id,
            float windSpeed,
            float remainingGameTime,
            float remainingTurnTime
    ) : current_client_id(currentTurnClientId),
        current_worm_id(current_worm_id),
        windSpeed(windSpeed),
        remainingGameTime(remainingGameTime),
        remainingTurnTime(remainingTurnTime) {}
};

class GameInstance {

    PhysicsSystem physics_system;
    InstancesManager instances_manager;
    ClientsWorms clientsWorms;
    TurnSystem turn_system;
    UpdatablesSystem updatables_system;
    ShotSystem shot_system;

    void assign_worms_to_clients(const std::list<Client *> &clients);

public:
    GameInstance(
            float xGravity,
            float yGravity,
            const GameScenarioData &scenario,
            const std::list<Client *> &clients,
            int rate
    );

    ClientsWorms get_clients_worms();
    void remove_from_clients_worms_map(size_t worm_id);

    std::vector<std::shared_ptr<Projectile>>& get_projectiles();
    GameState get_current_state();


    void update(const int it);
    bool is_client_turn(size_t id);

    // Actions
    void perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>)>& action);
    template <typename T>
    void perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>, T)>& action, T parameter);

    // Movement
    void start_moving_current_worm_left();
    void start_moving_current_worm_right();
    void stop_moving_current_worm();
    void jump_back_current_worm();
    void jump_forward_current_worm();

    // Weapon
    void start_aiming_up_current_worm();
    void start_aiming_down_current_worm();
    void stop_aiming_up_current_worm();
    void stop_aiming_down_current_worm();
    void change_weapon_for_current_worm(WeaponTypeDto weapon);

    // Shot
    void start_shot_for_current_worm();
    void end_shot_for_current_worm();

    // Projectile
    void change_projectile_count_down_for_current_worm(ProjectileCountDown time);

};


#endif

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
#include "Worm.h"
#include "InstancesManager.h"
#include "server_client.h"
#include "PhysicsSystem.h"
#include "TurnManager.h"
#include "UpdatablesSystem.h"
#include "ShotSystem.h"
#include "WindSystem.h"
#include "ExplosionsSystem.h"
#include "EntityCameraFocusSystem.h"
#include "GameState.h"
#include "Config.h"
#include "TurnSystemCfg.h"
#include "WormCfg.h"


typedef std::unordered_map<size_t, std::vector<std::shared_ptr<Worm>>> ClientsWorms;

class GameInstance {

    Config<WeaponCfg> weapons_cfg;
    Config<WormCfg> worms_cfg;
    Config<TurnSystemCfg> turn_system_cfg;
    // TODO Could do more cfgs

    b2World world;
    PhysicsSystem physics_system;
    InstancesManager instances_manager;
    ClientsWorms clients_worms;
    UpdatablesSystem updatables_system;
    ShotSystem shot_system;
    WindSystem wind_system;
    ExplosionsSystem explosions_system;
    EntityCameraFocusSystem entity_focus_system;
    TurnManager turn_system;

    void assign_worms_to_clients(const std::list<Client *> &clients);

public:
    GameInstance(
            float xGravity,
            float yGravity,
            const GameScenarioData &scenario,
            const std::list<Client *> &clients,
            int rate
    );

    GameState get_current_state();
    ClientsWorms get_clients_worms();
    std::vector<std::shared_ptr<Projectile>>& get_projectiles();
    std::vector<ExplosionDto>& get_explosions();
    int get_winner_client_id();

    void remove_from_clients_worms_map(int worm_id);

    bool update(const int it);
    bool is_client_turn(int id);
    std::vector<int> client_turn_order();

    // Actions
    void perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>)>& action);
    template <typename T>
    void perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>, T)>& action, T parameter);

    void input_action_to_current_worm(GameAction action);

    void change_weapon_for_current_worm(WeaponTypeDto weapon);
    void change_projectile_count_down_for_current_worm(ProjectileCountDown time);
    void toggle_cheat_mode_for_current_worm(CheatType cheat);


};


#endif

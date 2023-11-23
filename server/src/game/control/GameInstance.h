#ifndef SERVER_GAMEINSTANCE_H
#define SERVER_GAMEINSTANCE_H

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
#include "../../client/client.h"
#include "../systems/physics/PhysicsSystem.h"
#include "../systems/turns/TurnManager.h"
#include "../systems/instances/InstancesSystem.h"
#include "../systems/shot/ShotSystem.h"


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

    PhysicsSystem physicsSystem;
    InstancesManager instancesManager;
    ClientsWorms clientsWorms;
    TurnManager turnManager;
    InstancesSystem instances_system;
    ShotSystem shot_system;

    int active_worm_id;

    void assign_worms_to_clients(const std::list<Client *> &clients);

public:
    GameInstance(
            float xGravity,
            float yGravity,
            const GameScenarioData &scenario,
            const std::list<Client *> &clients,
            int rate
    );

    ClientsWorms getClientsWorms();
    std::vector<std::shared_ptr<Projectile>>& get_projectiles();
    GameState getCurrentState();

    void update(const int it);
    bool isClientsTurn(size_t id);

    // Actions
    // Movement
    void startMovingCurrentWormLeft();
    void startMovingCurrentWormRight();
    void stopMovingCurrentWorm();
    void jumpBackCurrentWorm();
    void jumpForwardCurrentWorm();

    // Weapon
    void start_aiming_up_current_worm();
    void start_aiming_down_current_worm();
    void stop_aiming_up_current_worm();
    void stop_aiming_down_current_worm();
    void change_weapon_for_current_worm(WeaponTypeDto weapon);

    // Shot
    void start_shot_for_current_worm();
    void end_shot_for_current_worm();






};


#endif

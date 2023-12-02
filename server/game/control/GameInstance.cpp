#include "GameInstance.h"
#include "Logger.h"

GameInstance::GameInstance(
    float xGravity,
    float yGravity,
    const GameScenarioData &scenarioData,
    const std::list<Client *> &clients,
    int rate
) :
    world(b2Vec2(xGravity, yGravity)),
    physics_system(rate, world, scenarioData),
    instances_manager(physics_system, scenarioData, worms_cfg.front(), weapons_cfg),
    clients_worms(),
    turn_system(rate, turn_system_cfg.front()),
    updatables_system(rate),
    shot_system(instances_manager),
    wind_system(world),
    explosions_system(instances_manager, world),
    entity_focus_system(rate) {
    assign_worms_to_clients(clients);
    turn_system.randomly_assign_clients_turn();

    auto on_worm_death = [this](size_t worm_id) {
        turn_system.remove_worm(worm_id);
        remove_from_clients_worms_map(worm_id);
    };
    instances_manager.register_worm_death_callback(on_worm_death);
}


bool GameInstance::update(const int it) {
    auto worms = instances_manager.get_worms();
    auto projectiles = instances_manager.get_projectiles();

    if (clients_worms.size() == 1) {
        // return true;
    } else if (clients_worms.empty()) {
        // return true;
    }

    int current_worm_id = turn_system.get_current_worm_id();
    std::shared_ptr<Worm> current_turn_worm = nullptr;
    current_turn_worm = instances_manager.get_worm(current_worm_id);
    updatables_system.update(it, worms, projectiles);
    physics_system.update();
    turn_system.update(it, worms, current_turn_worm, projectiles);
    shot_system.update(current_turn_worm);
    wind_system.update(projectiles);
    explosions_system.update(projectiles);
    entity_focus_system.update(it, worms, current_turn_worm, projectiles);
    instances_manager.update();
    return false;
}

bool GameInstance::is_client_turn(size_t id) {
    return turn_system.is_clients_turn(id);
}

GameState GameInstance::get_current_state() {
    return {
        turn_system.get_current_client_id(),
        turn_system.get_current_worm_id(),
        entity_focus_system.get_focused_entity_id(),
        wind_system.get_wind_speed(),
        turn_system.get_remaining_game_time(),
        turn_system.get_remaining_turn_time()
    };
}

int GameInstance::get_winner_client_id() {
    if (clients_worms.size() == 1) {
        return clients_worms.begin()->first; // Winner id
    } else if (clients_worms.empty()) {
        return 0; // Tie
    } else {
        return -1; // Game Ended by error
    }
}

ClientsWorms GameInstance::get_clients_worms() {
    return clients_worms;
}

std::vector<std::shared_ptr<Projectile>> &GameInstance::get_projectiles() {
    return instances_manager.get_projectiles();
}

std::vector<ExplosionDto>& GameInstance::get_explosions() {
    return explosions_system.get_explosions();
}

void GameInstance::assign_worms_to_clients(const std::list<Client *> &clients) {
    // Seed for random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Convert the unordered_map to a vector for shuffling
    std::vector<std::shared_ptr<Worm>> allWorms;
    for (const auto &[_, worm]: instances_manager.get_worms()) {
        allWorms.push_back(worm);
    }

    // Shuffle the worms randomly
    std::shuffle(allWorms.begin(), allWorms.end(), std::default_random_engine(std::rand()));

    // Calculate the number of worms per player
    size_t totalWorms = allWorms.size();
    size_t numPlayers = clients.size();
    size_t wormsPerPlayer = totalWorms / numPlayers;
    size_t extraWorms = totalWorms % numPlayers; // Extra worms for players with fewer worms

    // Iterate through each client
    for (const auto &client: clients) {
        int clientId = client->id;

        // Assign worms to the client
        size_t numWormsToAssign = wormsPerPlayer + (extraWorms > 0 ? 1 : 0);
        std::vector<std::shared_ptr<Worm>> assignedSubset(allWorms.begin(), allWorms.begin() + numWormsToAssign);

        // Adjust health for worms of players with fewer worms
        if (extraWorms > 0) {
            for (auto &worm: assignedSubset) {
                worm->adjust_health_to(worms_cfg.front().health.default_health);
            }
            --extraWorms;
        }

        // Remove assigned worms from the pool
        allWorms.erase(allWorms.begin(), allWorms.begin() + numWormsToAssign);


        // add client with its worms ids to the TurnManager
        std::list<int> wormIds;
        for (const auto &worm: assignedSubset) {
            wormIds.push_back(worm->Id());
        }
        turn_system.add_player(clientId, wormIds);

        // assign Worm* to clients ids
        clients_worms[clientId] = std::move(assignedSubset);
    }
}

void GameInstance::remove_from_clients_worms_map(size_t worm_id) {
    for (auto it = clients_worms.begin(); it != clients_worms.end();) {
        auto &worms = it->second;

        if (!worms.empty()) {
            auto removeIt = std::remove_if(worms.begin(), worms.end(),
                                           [worm_id](const auto &worm) {
                                               return worm->Id() == worm_id;
                                           }
            );
            worms.erase(removeIt, worms.end());

            // Check if the vector is empty after removal, and erase the entry if it is
            if (worms.empty()) {
                it = clients_worms.erase(it);
            } else {
                ++it;
            }
        } else {
            // Remove this entry
            it = clients_worms.erase(it);
        }
    }
}


// Actions
void GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>)> &action) {
    auto worm_id = turn_system.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instances_manager.get_worm(worm_id);
        if (worm)
            action(worm);
    }
}

template<typename T>
void
GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>, T)> &action, T parameter) {
    auto worm_id = turn_system.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instances_manager.get_worm(worm_id);
        if (worm)
            action(worm, parameter);
    }
}

// Movement
void GameInstance::start_moving_current_worm_left() {
    perform_action_on_current_worm([](auto worm) { worm->start_moving_left(); });
}

void GameInstance::start_moving_current_worm_right() {
    perform_action_on_current_worm([](auto worm) { worm->start_moving_right(); });
}

void GameInstance::stop_moving_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->stop_moving(); });
}

void GameInstance::jump_back_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->jump_backwards(); });
}

void GameInstance::jump_forward_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->jump_forward(); });
}

// Weapon
void GameInstance::start_aiming_up_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->start_aiming_up(); });
}

void GameInstance::start_aiming_down_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->start_aiming_down(); });
}

void GameInstance::stop_aiming_up_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->stop_aiming_up(); });
}

void GameInstance::stop_aiming_down_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->stop_aiming_down(); });
}

// Shot
void GameInstance::start_shot_for_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->start_shooting(); });
}

void GameInstance::end_shot_for_current_worm() {
    perform_action_on_current_worm([](auto worm) { worm->end_shooting(); });
}

void GameInstance::change_weapon_for_current_worm(WeaponTypeDto weapon) {
    perform_action_on_current_worm([weapon](auto worm) { worm->change_weapon(weapon); });
}

void GameInstance::change_projectile_count_down_for_current_worm(ProjectileCountDown count_down) {
    perform_action_on_current_worm([count_down](auto worm) { worm->change_projectile_count_down(count_down); });
}



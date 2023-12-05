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
    updatables_system(rate),
    shot_system(instances_manager),
    wind_system(world),
    explosions_system(instances_manager, world),
    entity_focus_system(),

    turn_system(
        instances_manager.get_projectiles(),
        instances_manager.get_worms(),
        turn_system_cfg.front().match_duration,
        turn_system_cfg.front().turn_duration,
        turn_system_cfg.front().time_after_ending_turn,
        rate
    ) {
    assign_worms_to_clients(clients);

    auto on_worm_destroyed = [this](int worm_id) {
        turn_system.remove(worm_id);
        remove_from_clients_worms_map(worm_id);
    };
    instances_manager.register_worm_destroyed_callback(on_worm_destroyed);
}


bool GameInstance::update(const int it) {
    auto worms = instances_manager.get_worms();
    auto projectiles = instances_manager.get_projectiles();

    if (clients_worms.size() == 1 || clients_worms.empty())
        return true;

    auto current_turn_worm = turn_system.get_current_worm();
    updatables_system.update(it, worms, projectiles);
    physics_system.update();
    shot_system.update(current_turn_worm);
    wind_system.update(projectiles);
    explosions_system.update(projectiles);
    entity_focus_system.update(worms, current_turn_worm, projectiles);
    instances_manager.update();
    turn_system.update(it);
    return turn_system.game_has_ended();
}

GameState GameInstance::get_current_state() {
    return {
        turn_system.current_client(),
        turn_system.get_current_worm_id(),
        entity_focus_system.get_focused_entity_id(),
        wind_system.get_wind_speed(),
        turn_system.get_game_remaining_time(),
        turn_system.get_turn_remaining_time()
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

std::vector<ExplosionDto> &GameInstance::get_explosions() {
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
        for (const auto &worm: assignedSubset) {
            turn_system.add_player(clientId, worm);
        }


        // assign Worm* to clients ids
        clients_worms[clientId] = std::move(assignedSubset);
    }
}

void GameInstance::remove_from_clients_worms_map(int worm_id) {
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

std::vector<int> GameInstance::client_turn_order(){
    return turn_system.get_order();
}

bool GameInstance::is_client_turn(int id) {
    return turn_system.current_client() == id;
}

// Actions
void GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>)> &action) {
    auto current_worm = turn_system.get_current_worm();
    if (current_worm) {
        action(current_worm);
    }
}

template<typename T>
void
GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>, T)> &action, T parameter) {
    auto current_worm = turn_system.get_current_worm();
    if (current_worm) {
        action(current_worm, parameter);
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

void GameInstance::on_client_disconnection(int client_id) {
    auto it = clients_worms.find(client_id);
    if (it != clients_worms.end()) {
        for (const auto& worm : it->second) {
            worm->Destroy();
        }
        clients_worms.erase(it);
    }
}

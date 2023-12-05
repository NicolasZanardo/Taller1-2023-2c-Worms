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

    auto on_worm_death = [this](int worm_id) {
        turn_system.remove(worm_id);
        remove_from_clients_worms_map(worm_id);
    };
    instances_manager.register_worm_death_callback(on_worm_death);
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
    } else if (clients_worms.empty() || turn_system.get_game_remaining_time() <= 0) {
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
    std::vector<std::shared_ptr<Worm>> all_worms;
    for (const auto &[_, worm]: instances_manager.get_worms()) {
        all_worms.push_back(worm);
    }

    // Shuffle the worms randomly
    std::shuffle(all_worms.begin(), all_worms.end(), std::default_random_engine(std::rand()));

    // Calculate the number of worms per player
    size_t total_worms = all_worms.size();
    size_t num_players = clients.size();
    size_t worms_per_player = total_worms / num_players;
    size_t extra_worms = total_worms % num_players; // Extra worms for players with fewer worms

    // Iterate through each client
    for (const auto &client: clients) {
        int clientId = client->id;

        // Assign worms to the client
        size_t num_worms_to_assign = worms_per_player + (extra_worms > 0 ? 1 : 0);
        std::vector<std::shared_ptr<Worm>> assigned_subset(all_worms.begin(), all_worms.begin() + num_worms_to_assign);

        // Adjust health for worms of players with fewer worms
        if (extra_worms > 0) {
            --extra_worms;
        } else {
            for (auto &worm: assigned_subset) {
                worm->adjust_health_to(worms_cfg.front().health.disadvantage_health);
            }
        }

        // Remove assigned worms from the pool
        all_worms.erase(all_worms.begin(), all_worms.begin() + num_worms_to_assign);


        // add client with its worms ids to the TurnManager
        for (const auto &worm: assigned_subset) {
            turn_system.add_player(clientId, worm);
        }


        // assign Worm* to clients ids
        clients_worms[clientId] = std::move(assigned_subset);
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

std::vector<int> GameInstance::client_turn_order() {
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

void GameInstance::input_action_to_current_worm(GameAction action) {
    perform_action_on_current_worm([action](auto worm) { worm->act(action); });
}

void GameInstance::change_weapon_for_current_worm(WeaponTypeDto weapon) {
    perform_action_on_current_worm([weapon](auto worm) { worm->change_weapon(weapon); });
}

void GameInstance::change_projectile_count_down_for_current_worm(ProjectileCountDown count_down) {
    perform_action_on_current_worm([count_down](auto worm) { worm->change_projectile_count_down(count_down); });
}

void GameInstance::toggle_cheat_mode_for_current_worm(CheatType cheat) {
    perform_action_on_current_worm([cheat](auto worm) { worm->toggle_cheat_mode(cheat); });
}


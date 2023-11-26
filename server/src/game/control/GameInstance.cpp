#include "GameInstance.h"
#include "../core/Logger.h"

GameInstance::GameInstance(
        float xGravity,
        float yGravity,
        const GameScenarioData &scenarioData,
        const std::list<Client *> &clients,
        int rate
) :
    physics_system(rate, xGravity, yGravity, scenarioData),
    instances_manager(physics_system, scenarioData),
    clientsWorms(),
    turn_system(rate),
    updatables_system(rate),
    shot_system(instances_manager) {

    assign_worms_to_clients(clients);
    turn_system.randomly_assign_clients_turn();

    auto on_worm_death = [this](size_t worm_id) {
        turn_system.remove_worm(worm_id);
        remove_from_clients_worms_map(worm_id);
    };
    instances_manager.register_worm_death_callback(on_worm_death);
}


void GameInstance::update(const int it) {
    auto worms = instances_manager.get_worms();
    /* if (worms.size() == 1) {
     * Client won
    } else if (worms.size() == 0) {
        Tie
    }
     */

    int current_worm_id = turn_system.get_current_worm_id();
    std::shared_ptr<Worm> active_worm = nullptr;
    if (current_worm_id != -1) {
        active_worm = instances_manager.get_worm(current_worm_id);
        if (active_worm) {
            // Logger::log_position("Worm", active_worm->X(), active_worm->Y());
        }
    }
    updatables_system.update(it, worms, get_projectiles());
    physics_system.update(worms);
    turn_system.update(it, worms, active_worm);
    shot_system.update(active_worm);
    instances_manager.update();
}

bool GameInstance::is_client_turn(size_t id) {
    return turn_system.is_clients_turn(id);
}

GameState GameInstance::get_current_state() {
    return GameState(
        turn_system.get_current_client_id(),
        turn_system.get_current_worm_id(),
        1.0f, // wind physicsSystem
            turn_system.get_remaining_game_time(),
        turn_system.get_remaining_turn_time()
    );
}

ClientsWorms GameInstance::get_clients_worms() {
    return clientsWorms;
}

std::vector<std::shared_ptr<Projectile>>& GameInstance::get_projectiles() {
    return instances_manager.get_projectiles();
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
        size_t clientId = client->id;

        // Assign worms to the client
        size_t numWormsToAssign = wormsPerPlayer + (extraWorms > 0 ? 1 : 0);
        std::vector<std::shared_ptr<Worm>> assignedSubset(allWorms.begin(), allWorms.begin() + numWormsToAssign);

        // Adjust health for worms of players with fewer worms
        if (extraWorms > 0) {
            for (auto &worm: assignedSubset) {
                worm->heal(25);
            }
            --extraWorms;
        }

        // Remove assigned worms from the pool
        allWorms.erase(allWorms.begin(), allWorms.begin() + numWormsToAssign);


        // add client with its worms ids to the TurnManager
        std::list<size_t> wormIds;
        for (const auto &worm : assignedSubset) {
            wormIds.push_back(worm->Id());
        }
        turn_system.add_player(clientId, wormIds);

        // assign Worm* to clients ids
        clientsWorms[clientId] = std::move(assignedSubset);
    }
}

void GameInstance::remove_from_clients_worms_map(size_t worm_id) {
    for (auto& [client_id, worms] : clientsWorms) {

        auto it = std::remove_if(worms.begin(), worms.end(),
                                 [worm_id](const auto& worm) {
                                     return worm->Id() == worm_id;
                                 }
        );
        worms.erase(it, worms.end());
    }
}


// Actions
void GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>)>& action) {
    auto worm_id = turn_system.get_current_worm_id();
    if (worm_id != -1) {
        auto worm = instances_manager.get_worm(worm_id);
        if (worm)
            action(worm);
    }
}

template <typename T>
void GameInstance::perform_action_on_current_worm(const std::function<void(std::shared_ptr<Worm>, T)>& action, T parameter) {
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


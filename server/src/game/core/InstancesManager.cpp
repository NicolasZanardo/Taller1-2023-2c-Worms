#include "InstancesManager.h"
#include <iostream>

InstancesManager::InstancesManager(
        PhysicsSystem &physicsSystem,
        const GameScenarioData &gameScenarioData
) : physicsSystem(physicsSystem) {
    instantiate_worms(gameScenarioData);
}

void update() {

}

void InstancesManager::update() {
    for (const auto& projectile: projectiles_to_add) {
        std::cout << "Adding the spawned projectile to the vector\n";
        projectiles.push_back(projectile);
    }
    projectiles_to_add.clear();

    remove_dead_instances(projectiles);
    remove_dead_instances(worms);
}

template<typename T>
void InstancesManager::remove_dead_instances(std::vector<std::shared_ptr<T>>& instances_vec) {
    instances_vec.erase(std::remove_if(instances_vec.begin(), instances_vec.end(),
                                       [](const std::shared_ptr<T>& e) { return !e->is_active; }),
                        instances_vec.end());
}

// Specialization definition for Worm type
void InstancesManager::remove_dead_instances(std::unordered_map<size_t, std::shared_ptr<Worm>>& worms_map) {
    for (auto it = worms_map.begin(); it != worms_map.end();) {
        if (!it->second->is_active) {
            worm_death_callback(it->second->id);
            it = worms_map.erase(it);
            std::cout << "After deletion the worms map size is: " << worms_map.size() << std::endl;
        } else {
            ++it;
        }
    }
}


std::shared_ptr<Worm> InstancesManager::instantiate_worm(const WormScenarioData &wormScenarioData) {
    auto worm = std::shared_ptr<Worm>(new Worm(++total_entities_created));
    worm->body = physicsSystem.spawn_worm(wormScenarioData, worm);
    return worm;
}

void InstancesManager::instantiate_worms(const GameScenarioData &gameScenarioData) {
    for (const WormScenarioData& wormScenarioData: gameScenarioData.worms) {
        auto worm = instantiate_worm(wormScenarioData);
        worms.try_emplace(worm->id, worm);
    }
}

std::unordered_map<size_t, std::shared_ptr<Worm>> InstancesManager::get_worms() {
    return worms;
}

std::shared_ptr<Worm> InstancesManager::get_worm(size_t id) {
    auto it = worms.find(id);
    return (it != worms.end()) ? it->second : nullptr;
}

// Projectiles
void InstancesManager::instantiate_projectiles(std::unique_ptr<CShot> shot) {
    for (const auto& projectile_info: shot->Projectiles()) {
        auto projectile = std::shared_ptr<Projectile>(
            new Projectile(++total_entities_created, projectile_info)
            );
        projectile->body = physicsSystem.spawn_projectile(projectile_info, shot->ShotAngle(), projectile);
        projectiles_to_add.push_back(projectile);
    }
}

std::vector<std::shared_ptr<Projectile>>& InstancesManager::get_projectiles() {
    return projectiles;
}

void InstancesManager::register_worm_death_callback(std::function<void(size_t)> callback) {
        worm_death_callback = std::move(callback);
}

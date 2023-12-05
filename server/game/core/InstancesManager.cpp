#include "InstancesManager.h"
#include "ProjectileFactory.h"
#include <iostream>

typedef Config<WeaponCfg> &config;

InstancesManager::InstancesManager(
    PhysicsSystem &physicsSystem,
    const GameScenarioData &gameScenarioData,
    WormCfg &worms_cfg,
    config weapons_cfg
) : weapons_cfg(weapons_cfg),
    worms_cfg(worms_cfg),
    physics_system(physicsSystem) {
    instantiate_worms(gameScenarioData);
}

void InstancesManager::update() {
    for (const auto &projectile: projectiles_to_add) {
        projectiles.push_back(projectile);
    }
    projectiles_to_add.clear();
    remove_dead_instances(projectiles);
    remove_dead_instances(worms);
}

template<typename T>
void InstancesManager::remove_dead_instances(std::vector<std::shared_ptr<T>> &instances_vec) {
    instances_vec.erase(
        std::remove_if(instances_vec.begin(), instances_vec.end(),
            [](const std::shared_ptr<T> &e) { return !e->IsActive(); }),
    instances_vec.end());
}

// Specialization definition for Worm type
void InstancesManager::remove_dead_instances(std::unordered_map<int, std::shared_ptr<Worm>> &worms_map) {
    for (auto it = worms_map.begin(); it != worms_map.end();) {
        if (!it->second->is_active) {
            worm_death_callback(it->second->id);
            it = worms_map.erase(it);
        } else {
            ++it;
        }
    }
}


std::shared_ptr<Worm> InstancesManager::instantiate_worm(
    const WormScenarioData &wormScenarioData
) {
    auto worm = std::shared_ptr<Worm>(new Worm(++total_entities_created, worms_cfg,weapons_cfg));
    worm->body = physics_system.spawn_worm(wormScenarioData, worm, worms_cfg);
    return worm;
}

void InstancesManager::instantiate_worms(const GameScenarioData &gameScenarioData) {
    for (const WormScenarioData &wormScenarioData: gameScenarioData.worms) {
        auto worm = instantiate_worm(wormScenarioData);
        worms.try_emplace(worm->id, worm);
    }
}

std::unordered_map<int, std::shared_ptr<Worm>>& InstancesManager::get_worms() {
    return worms;
}

std::shared_ptr<Worm> InstancesManager::get_worm(int id) {
    auto it = worms.find(id);
    return (it != worms.end()) ? it->second : nullptr;
}

// Projectiles
void InstancesManager::instantiate_projectiles(std::unique_ptr<CShot> shot) {
    for (const auto &projectile_info: shot->Projectiles()) {
        auto projectile = ProjectileFactory::create_projectile(++total_entities_created, projectile_info);
        projectile->body = physics_system.spawn_projectile(projectile_info, projectile);
        projectiles_to_add.push_back(projectile);
    }
}

void InstancesManager::instantiate_fragment_projectile(
    const std::unique_ptr<FragmentsInfo> &info,
    float x,
    float y,
    b2Vec2 speed
) {
    auto projectile = ProjectileFactory::create_fragment_projectile(++total_entities_created, info);
    projectile->body = physics_system.spawn_fragment_projectile(
        projectile, info, x, y, speed
    );
    projectiles_to_add.push_back(projectile);
}

std::vector<std::shared_ptr<Projectile>>&InstancesManager::get_projectiles() {
    return projectiles;
}

void InstancesManager::register_worm_destroyed_callback(std::function<void(int)> callback) {
    worm_death_callback = std::move(callback);
}

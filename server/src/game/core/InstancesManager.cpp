#include "InstancesManager.h"
#include "../model/projectiles/Projectile.h"
#include <iostream>

InstancesManager::InstancesManager(
        PhysicsSystem &physicsSystem,
        const GameScenarioData &gameScenarioData
) : physicsSystem(physicsSystem) {
    createWorms(gameScenarioData);
}

std::shared_ptr<Worm> InstancesManager::instantiate_worm(const WormScenarioData &wormScenarioData) {
    auto worm = std::shared_ptr<Worm>(new Worm(++total_entities_created));
    b2Body *body = physicsSystem.spawn_worm(wormScenarioData, worm);
    worm->movement = std::make_shared<WormMovement>(body);
    return worm;
}

void InstancesManager::createWorms(const GameScenarioData &gameScenarioData) {
    for (const WormScenarioData& wormScenarioData: gameScenarioData.worms) {
        auto worm = instantiate_worm(wormScenarioData);
        worms.try_emplace(worm->id, worm);
    }
}

std::unordered_map<size_t, std::shared_ptr<Worm>> InstancesManager::getWorms() {
    return worms;
}

std::shared_ptr<Worm> InstancesManager::getWorm(size_t id) {
    return worms[id];
}

std::vector<std::shared_ptr<Projectile>>& InstancesManager::get_projectiles() {
    return projectiles;;
}

// Projectiles
void InstancesManager::instantiate_projectiles(std::unique_ptr<Shot> shot) {
    for (const auto& projectile_info: shot->Projectiles()) {
        auto projectile = std::shared_ptr<Projectile>(new Projectile(++total_entities_created, projectile_info->from_weapon));
        b2Body *body = physicsSystem.spawn_projectile(projectile_info, shot->ShotAngle());
        projectile->movement = std::make_unique<ProjectileMovement>(body);
        projectiles.push_back(projectile);
    }

}

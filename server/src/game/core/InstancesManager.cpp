#include "InstancesManager.h"
#include <iostream>

InstancesManager::InstancesManager(
        PhysicsSystem &physicsSystem,
        const GameScenarioData &gameScenarioData
) : physicsSystem(physicsSystem) {
    createWorms(gameScenarioData);
}

std::shared_ptr<Worm> InstancesManager::instantiate_worm(const WormScenarioData &wormScenarioData) {
    auto worm = std::shared_ptr<Worm>(new Worm(++total_entities_created)); // TODO SHARED PTR
    b2Body *body = physicsSystem.spawn_worm(wormScenarioData, worm);
    worm->movement = std::make_shared<WormMovement>(body);
    std::cout << "Worm with id: " << total_entities_created << "was created at" <<
    "x: " << worm->movement->x() << " y: " << worm->movement->y() << std::endl;
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

// Projectiles

std::shared_ptr<Projectile> instantiate_projectile(std::unique_ptr<Shot> shot) {
    for (auto projectile: shot->projectiles) {
        projectile
    }

}
#include "InstancesManager.h"

InstancesManager::InstancesManager(
        PhysicsSystem &physicsSystem,
        const GameScenarioData &gameScenarioData
) : physicsSystem(physicsSystem) {
    createWorms(gameScenarioData);
}

Worm * InstancesManager::createWorm(const WormScenarioData &wormScenarioData) {
    auto worm = new Worm(total_entities_created++);
    b2Body *body = physicsSystem.spawn_worm(wormScenarioData, worm);
    worm->body = body;
    return worm;
}

void InstancesManager::createWorms(const GameScenarioData &gameScenarioData) {
    for (const WormScenarioData& wormScenarioData: gameScenarioData.worms) {
        auto worm = createWorm(wormScenarioData);
        worms.try_emplace(worm->id, worm);
    }
}

std::unordered_map<size_t, Worm *> InstancesManager::getWorms() {
    return worms;
}

Worm * InstancesManager::getWorm(size_t id) {
    return worms[id];
}
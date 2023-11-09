#include "InstancesManager.h"

InstancesManager::InstancesManager(PhysicsSystem &physicsSystem): physicsSystem(physicsSystem) {}

Worm *InstancesManager::create_worm(WormScenarioData& wormScenarioData) {
    auto worm = new Worm(total_entities_created++);
    b2Body* body = physicsSystem.spawn_worm(wormScenarioData, worm);
    worm->body = body;

    return worm;
}

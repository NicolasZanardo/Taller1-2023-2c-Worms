#include "InstancesManager.h"

InstancesManager::InstancesManager(PhysicsSystem &physicsSystem): physicsSystem(physicsSystem) {}

Worm *InstancesManager::create_worm(WormScenarioData& wormScenarioData) {
    b2Body* body = physicsSystem.spawn_worm(wormScenarioData);
    auto worm = new Worm(total_entities_created++, body);
    worms[total_entities_created] = worm;
    return worm;
}

Worm* InstancesManager::get_worm(const size_t id) {
    return worms[id]; // TODO Non existing Worm
}

size_t InstancesManager::amount_of_worms() {
    return worms.size();
}
#include "EntityManager.h"

EntityManager::EntityManager(PhysicsSystem &physicsSystem): physicsSystem(physicsSystem) {}

Worm *EntityManager::create_worm(WormScenarioData& wormScenarioData) {
    b2Body* body = physicsSystem.spawn_worm(wormScenarioData);
    auto worm = new Worm(total_entities_created++, body);
    worms[total_entities_created] = worm;
    return worm;
}

Worm* EntityManager::get_worm(const size_t id) {
    return worms[id]; // TODO Non existing Worm
}

size_t EntityManager::amount_of_worms() {
    return worms.size();
}
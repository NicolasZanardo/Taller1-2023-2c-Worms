#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include <vector>
#include <unordered_map>
#include "Worm.h"
#include "../../simulation/PhysicsSystem.h"

class InstancesManager {
private:
    size_t total_entities_created = 0;
    PhysicsSystem& physicsSystem;

    // Worm id to worm map
    std::unordered_map<size_t, Worm *> worms;
    Worm* createWorm(const WormScenarioData &wormScenarioData);
public:
    InstancesManager(PhysicsSystem& physicsSystem, const GameScenarioData& map);

    // Worms
    void createWorms(const GameScenarioData& map);
    std::unordered_map<size_t, Worm *> getWorms();
    Worm * getWorm(size_t wormId);
};


#endif

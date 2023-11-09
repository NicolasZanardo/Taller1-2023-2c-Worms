#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include  <vector>
#include "Worm.h"
#include "../../simulation/PhysicsSystem.h"

class InstancesManager {
private:
    size_t total_entities_created = 0;
    PhysicsSystem& physicsSystem;
public:
    InstancesManager(PhysicsSystem& physicsSystem);


    // Worms
    Worm* create_worm(WormScenarioData& worm);
};


#endif

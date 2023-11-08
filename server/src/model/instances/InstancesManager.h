#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include  <unordered_map>
#include "Worm.h"
#include "../../simulation/PhysicsSystem.h"

class InstancesManager {
private:
    size_t total_entities_created = 0;
    PhysicsSystem& physicsSystem;
    std::unordered_map<size_t, Worm*> worms;
public:
    InstancesManager(PhysicsSystem& physicsSystem);
    Worm* create_worm(WormScenarioData& worm);
    Worm* get_worm(const size_t id);
    size_t amount_of_worms();
};


#endif

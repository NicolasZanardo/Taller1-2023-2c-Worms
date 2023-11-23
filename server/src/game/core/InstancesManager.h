#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "../model/worm/Worm.h"
#include "../systems/physics/PhysicsSystem.h"
#include "../model/projectiles/Projectile.h"

class InstancesManager {
private:
    size_t total_entities_created = 0;
    PhysicsSystem& physicsSystem;

    // Worm id to worm map
    std::unordered_map<size_t, std::shared_ptr<Worm>> worms;
    std::vector<std::shared_ptr<Projectile>> projectiles;

    std::shared_ptr<Worm> instantiate_worm(const WormScenarioData &wormScenarioData);

public:
    InstancesManager(PhysicsSystem& physicsSystem, const GameScenarioData& map);

    // Worms
    void createWorms(const GameScenarioData& map);
    std::unordered_map<size_t, std::shared_ptr<Worm>> getWorms();
    std::shared_ptr<Worm> getWorm(size_t wormId);
    std::vector<std::shared_ptr<Projectile>>& get_projectiles();

    // Projectiles
    void instantiate_projectiles(std::unique_ptr<Shot> shot);
};


#endif

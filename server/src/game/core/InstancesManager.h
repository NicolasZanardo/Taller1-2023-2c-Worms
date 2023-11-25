#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include "../model/worm/Worm.h"
#include "../systems/physics/PhysicsSystem.h"
#include "../model/projectiles/Projectile.h"

class InstancesManager {
private:
    size_t total_entities_created = 0;
    PhysicsSystem& physics_system;

    // Worm id to worm map
    std::unordered_map<size_t, std::shared_ptr<Worm>> worms;
    std::shared_ptr<Worm> instantiate_worm(const WormScenarioData &wormScenarioData);


    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<std::shared_ptr<Projectile>> projectiles_to_add;

    // Supply crate
    // std::vector<std::shared_ptr<SupplyCrate>> supply_crates;
    // std::vector<std::shared_ptr<SupplyCrate>> supply_crates_to_add;

    template<typename T>
    void remove_dead_instances(std::vector<std::shared_ptr<T>>& instances_vec);

    // Specialization for Worm type
    void remove_dead_instances(std::unordered_map<size_t, std::shared_ptr<Worm>>& worms);

    std::function<void(size_t)> worm_death_callback;

public:
    InstancesManager(PhysicsSystem& physicsSystem, const GameScenarioData& map);
    void update();


    // Worms
    void instantiate_worms(const GameScenarioData& gameScenarioData);
    std::unordered_map<size_t, std::shared_ptr<Worm>> get_worms();
    std::shared_ptr<Worm> get_worm(size_t id);

    void register_worm_death_callback(std::function<void(size_t)> callback);

    // Projectiles
    void instantiate_projectiles(std::unique_ptr<CShot> shot);
    std::vector<std::shared_ptr<Projectile>>& get_projectiles();
};


#endif

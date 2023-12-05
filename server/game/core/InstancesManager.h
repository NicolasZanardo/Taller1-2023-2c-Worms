#ifndef SERVER_ENTITYMANAGER_H
#define SERVER_ENTITYMANAGER_H

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>
#include "Worm.h"
#include "PhysicsSystem.h"
#include "Projectile.h"
#include "Config.h"
#include "WormCfg.h"

class InstancesManager {
private:
    Config<WeaponCfg>& weapons_cfg;
    WormCfg& worms_cfg;
    int total_entities_created = 0;
    PhysicsSystem &physics_system;

    // Worm id to worm map
    std::unordered_map<int, std::shared_ptr<Worm>> worms;

    std::shared_ptr<Worm> instantiate_worm(const WormScenarioData &wormScenarioData);


    std::vector<std::shared_ptr<Projectile>> projectiles;
    std::vector<std::shared_ptr<Projectile>> projectiles_to_add;

    // Supply crate
    // std::vector<std::shared_ptr<SupplyCrate>> supply_crates;
    // std::vector<std::shared_ptr<SupplyCrate>> supply_crates_to_add;

    template<typename T>
    void remove_dead_instances(std::vector<std::shared_ptr<T>> &instances_vec);

    // Specialization for Worm type
    void remove_dead_instances(std::unordered_map<int, std::shared_ptr<Worm>> &worms);

    std::function<void(int)> worm_death_callback;

public:
    InstancesManager(
        PhysicsSystem &physicsSystem,
        const GameScenarioData &map,
        WormCfg &worms_cfg,
        Config<WeaponCfg> &weapons_cfg
        );

    void update();


    // Worms
    void instantiate_worms(const GameScenarioData &gameScenarioData);

    std::unordered_map<int, std::shared_ptr<Worm>>& get_worms();

    std::shared_ptr<Worm> get_worm(int id);

    void register_worm_death_callback(std::function<void(int)> callback);

    // Projectiles
    void instantiate_projectiles(std::unique_ptr<CShot> shot);

    void instantiate_fragment_projectile(
        const std::unique_ptr<FragmentsInfo>& info,
        float x,
        float y,
        b2Vec2 speed
    );

    std::vector<std::shared_ptr<Projectile>>& get_projectiles();
};


#endif

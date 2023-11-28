#ifndef TP_WORMS_EXPLOSIONSSYSTEM_H
#define TP_WORMS_EXPLOSIONSSYSTEM_H

#include <memory>
#include "../../core/InstancesManager.h"

class ExplosionsSystem {
    InstancesManager &instances_manager;
    b2World &world;
    const float FRAGMENTS_EXPLOSION_CONSTANT = 0.04f;

    void instantiate_individual_fragment(
        int actual,
        const std::unique_ptr<FragmentsInfo> &info,
        const std::unique_ptr<CExplosion> &explosion
    );

public:
    explicit ExplosionsSystem(InstancesManager &instances_manager, b2World &world);

    void update(const std::vector<std::shared_ptr<Projectile>> &projectiles);
};


#endif //TP_WORMS_EXPLOSIONSSYSTEM_H

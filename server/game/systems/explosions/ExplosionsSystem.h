#ifndef TP_WORMS_EXPLOSIONSSYSTEM_H
#define TP_WORMS_EXPLOSIONSSYSTEM_H

#include <memory>
#include <vector>
#include "InstancesManager.h"
#include "ExplosionDto.h"

class ExplosionsSystem {
    InstancesManager &instances_manager;
    b2World &world;
    const float FRAGMENTS_EXPLOSION_CONSTANT = 0.04f;
    std::vector<ExplosionDto> explosions;

    void instantiate_individual_fragment(
        int actual,
        const std::unique_ptr<FragmentsInfo> &info,
        const std::unique_ptr<CExplosion> &explosion
    );

public:
    explicit ExplosionsSystem(InstancesManager &instances_manager, b2World &world);

    std::vector<ExplosionDto>& get_explosions();

    void update(const std::vector<std::shared_ptr<Projectile>> &projectiles);
};


#endif //TP_WORMS_EXPLOSIONSSYSTEM_H

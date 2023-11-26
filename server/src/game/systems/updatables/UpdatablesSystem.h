#ifndef TP_WORMS_UPDATABLESSYSTEM_H
#define TP_WORMS_UPDATABLESSYSTEM_H

#include <unordered_map>
#include "../../model/worm/Worm.h"
#include "../../core/InstancesManager.h"

class UpdatablesSystem {
public:
    UpdatablesSystem() = default;
    void update(
        int it,
        const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms,
        const std::vector<std::shared_ptr<Projectile>> &projectiles
        );
};

#endif

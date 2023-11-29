#ifndef TP_WORMS_UPDATABLESSYSTEM_H
#define TP_WORMS_UPDATABLESSYSTEM_H

#include <unordered_map>
#include "Worm.h"
#include "InstancesManager.h"

class UpdatablesSystem {
    int rate;
public:
    UpdatablesSystem(int rate);
    void update(
        int it,
        const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
        const std::vector<std::shared_ptr<Projectile>> &projectiles
        ) const;
};

#endif

#include "InstancesSystem.h"

void InstancesSystem::update(
    const int it,
    const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms,
    const std::vector<std::shared_ptr<Projectile>> &projectiles
) {
    for (const auto& [_, worm]: worms) {
        worm->update(it);
    }
    for (const auto&  projectile: projectiles) {
        projectile->update(it);
    }

}

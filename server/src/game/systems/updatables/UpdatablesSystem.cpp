#include "UpdatablesSystem.h"

UpdatablesSystem::UpdatablesSystem(int rate): rate(rate)  {}

void UpdatablesSystem::update(
    const int it,
    const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
    const std::vector<std::shared_ptr<Projectile>> &projectiles
) const {
    for (const auto& [_, worm]: worms) {
        worm->update(it, rate);
    }
    for (const auto&  projectile: projectiles) {
        projectile->update(it, rate);
    }
}


#include "InstancesSystem.h"

void InstancesSystem::update(
    const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms
) {
    for (const auto& [_, worm]: worms) {
        worm->update();
    }

    // Do Projectiles need to update anything?
}

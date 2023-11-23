#include "InstancesSystem.h"

void InstancesSystem::update(
    const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms
) {
    for (auto [id, worm]: worms) {
        worm->update();
    }
}

#include "InstancesSystem.h"

void InstancesSystem::update(
    const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms,
    std::shared_ptr<Worm> &current_worm
) {
    for (auto [id, worm]: worms) {
        worm->update();
    }
}

#include "ShotSystem.h"
#include "Logger.h"

ShotSystem::ShotSystem(InstancesManager &instances_manager): instances_manager(instances_manager) {}

void ShotSystem::update(const std::shared_ptr<Worm>& current_worm) {
    if (current_worm) {
        auto shot = current_worm->shot_component();
        if (shot) {
            instances_manager.instantiate_projectiles(std::move(shot));
        }
    }
}
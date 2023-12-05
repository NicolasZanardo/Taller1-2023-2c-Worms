#include "EntityCameraFocusSystem.h"
#include <iostream>
EntityCameraFocusSystem::EntityCameraFocusSystem() :
    focused_entity(1) {}

int EntityCameraFocusSystem::get_focused_entity_id() const {
    return focused_entity;
}

void EntityCameraFocusSystem::update(
    const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
    const std::shared_ptr<Worm> &current_turn_worm,
    const std::vector<std::shared_ptr<Projectile>> &projectiles
) {
    // If a projectile was shot camera should focused it
    // Check is active, could have just been destroyed on this tick and an inactive projectile would try to be focused
    if (!projectiles.empty() && projectiles.front()->IsActive()) {
        focused_entity = projectiles.front()->Id();
        return;
    }

    // else if current worm hasnt done an ending turn action
    // Could have just been destroyed on this tick and an inactive worm would try to be focused
    if (current_turn_worm && current_turn_worm->IsActive() && !current_turn_worm->has_done_ending_turn_action()) {
        focused_entity = current_turn_worm->Id();
        return;
    }

    // else focus the fastest flying worm
    if (!worms.empty()) {
        std::shared_ptr<Worm> fastest_worm = worms.cbegin()->second;
        for (const auto &[_, worm]: worms) {
            if (worm->IsActive() && worm->get_body()->is_moving_faster_than(fastest_worm->get_body())) {
                fastest_worm = worm;
            }
        }
        if (!fastest_worm->is_still()) {
            if (fastest_worm != current_turn_worm) {
                focused_entity = fastest_worm->Id();
                return;
            }
        }
    }
    focused_entity = -1;
}

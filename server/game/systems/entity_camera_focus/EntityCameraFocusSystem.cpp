#include "EntityCameraFocusSystem.h"
#include <iostream>
EntityCameraFocusSystem::EntityCameraFocusSystem(int rate) :
    is_focusing_flying_worm(false), focused_entity(1), rate(rate), changing_focus_cooldown(COOLDOWN) {}

int EntityCameraFocusSystem::get_focused_entity_id() const {
    return focused_entity;
}

void EntityCameraFocusSystem::update(
    int it,
    const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
    const std::shared_ptr<Worm> &current_turn_worm,
    const std::vector<std::shared_ptr<Projectile>> &projectiles
) {
    // Could have just been destroyed on this tick and an inactive projectile would try to be focused
    if (!projectiles.empty() && projectiles.front()->IsActive()) {
        focused_entity = projectiles.front()->Id();
        is_focusing_flying_worm = false;
        return;
    }

    // Could have just been destroyed on this tick and an inactive worm would try to be focused
    if (current_turn_worm && current_turn_worm->IsActive()) {
        focused_entity = current_turn_worm->Id();
        is_focusing_flying_worm = false;
        return;
    }

    if (!is_focusing_flying_worm || changing_focus_cooldown <= 0) {
        std::shared_ptr<Worm> fastest_worm;
        if (!worms.empty()) {
            fastest_worm = worms.cbegin()->second;
            for (const auto &[_, worm]: worms) {
                if (worm->body->is_moving_faster_than(fastest_worm->body) && worm->IsActive()) {
                    fastest_worm = worm;
                }
            }
            is_focusing_flying_worm = true;
            focused_entity = fastest_worm->Id();
            changing_focus_cooldown = COOLDOWN;
            return;
        }
    } else {
        changing_focus_cooldown -= it * rate;
        return;
    }
    is_focusing_flying_worm = false;
    focused_entity = -1;
}

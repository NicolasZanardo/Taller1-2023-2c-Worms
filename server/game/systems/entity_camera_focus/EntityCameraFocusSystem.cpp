#include "EntityCameraFocusSystem.h"
#include <iostream>
EntityCameraFocusSystem::EntityCameraFocusSystem(int rate) :
    is_focusing_flying_worm(false), focused_entity(1), rate(rate), change_focus_of_flying_worm_cooldown(COOLDOWN) {}

int EntityCameraFocusSystem::get_focused_entity_id() const {
    return focused_entity;
}

void EntityCameraFocusSystem::update(
    int it,
    const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
    const std::shared_ptr<Worm> &current_turn_worm,
    const std::vector<std::shared_ptr<Projectile>> &projectiles
) {
    // If a projectile was shot camera should focused it
    // Check is active, could have just been destroyed on this tick and an inactive projectile would try to be focused
    if (!projectiles.empty() && projectiles.front()->IsActive()) {
        focused_entity = projectiles.front()->Id();
        is_focusing_flying_worm = false;
        return;
    }

    // If there is no projectile, focused actual worm if he hasnt done an ending turn action yet
    // Could have just been destroyed on this tick and an inactive worm would try to be focused
    if (current_turn_worm && current_turn_worm->IsActive() &&
    !current_turn_worm->has_done_ending_turn_action()
    ) {
        focused_entity = current_turn_worm->Id();
        is_focusing_flying_worm = false;
        return;
    }

    // If its still not focusing a flying worm
    // or it was focusing one but the cooldown to search a faster flying one changed try focus the faster one
    if (!is_focusing_flying_worm || change_focus_of_flying_worm_cooldown <= 0) {
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
            change_focus_of_flying_worm_cooldown = COOLDOWN;
            return;
        }
    } else {
        // if is still with the same flying worm decrease cooldown
        change_focus_of_flying_worm_cooldown -= it * rate;
        return;
    }
    // None of the cases not specific focus
    is_focusing_flying_worm = false;
    focused_entity = -1;
}

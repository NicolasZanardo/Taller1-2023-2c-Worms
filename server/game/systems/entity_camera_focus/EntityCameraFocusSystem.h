#ifndef TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H
#define TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Worm.h"
#include "Projectile.h"

class EntityCameraFocusSystem {
    const int COOLDOWN = 1500;
    bool is_focusing_flying_worm;
    int focused_entity;
    const int rate;
    int change_focus_of_flying_worm_cooldown{};
public:
    explicit EntityCameraFocusSystem(int rate);

    void update(
        int it,
        const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
        const std::shared_ptr<Worm> &current_turn_worm,
        const std::vector<std::shared_ptr<Projectile>> &projectiles
    );

    int get_focused_entity_id() const;
};


#endif //TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H

#ifndef TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H
#define TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Worm.h"
#include "Projectile.h"

class EntityCameraFocusSystem {
    int focused_entity;
public:
    explicit EntityCameraFocusSystem();

    void update(
        const std::unordered_map<int, std::shared_ptr<Worm>> &worms,
        const std::shared_ptr<Worm> &current_turn_worm,
        const std::vector<std::shared_ptr<Projectile>> &projectiles
    );

    int get_focused_entity_id() const;
};


#endif //TP_WORMS_ENTITYCAMERAFOCUSSYSTEM_H

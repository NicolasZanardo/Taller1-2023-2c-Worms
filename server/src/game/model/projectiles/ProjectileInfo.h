#ifndef TP_WORMS_PROJECTILEINFO_H
#define TP_WORMS_PROJECTILEINFO_H

#include <memory>
#include "../core/Updatable.h"
#include "../weapons/Damage.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../../../../../common_base/constants.h"

class ProjectileInfo {
public:
    size_t shooter_id;
    float shot_angle;
    char facing_sign;
    Damage &damage;
    float power;
    float origin_x;
    float origin_y;
    float radius = PROJECTILE_RADIUS; // TODO CONSTANT FOR ALL PROJECTILES NOW,
    WeaponTypeDto from_weapon;

    ProjectileInfo(
        size_t shooter_id,
        float shot_angle,
        char facing_sign,
        Damage &damage,
        float power,
        float origin_x,
        float origin_y,
        WeaponTypeDto from_weapon
    );

};


#endif

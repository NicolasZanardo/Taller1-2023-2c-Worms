#ifndef TP_WORMS_PROJECTILEINFO_H
#define TP_WORMS_PROJECTILEINFO_H

#include <memory>
#include "../core/Updatable.h"
#include "../weapons/Damage.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"

class ProjectileInfo {
public:
    Damage& damage;
    float power;
    float origin_x;
    float origin_y;
    float radius = 0.5f; // TODO CONSTANT FOR ALL PROJECTILES NOW
    WeaponTypeDto from_weapon;

    ProjectileInfo(Damage& damage, float power, float origin_x, float origin_y, WeaponTypeDto from_weapon);

    float damage_radius() const;
};


#endif

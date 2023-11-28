#ifndef TP_WORMS_PROJECTILEINFO_H
#define TP_WORMS_PROJECTILEINFO_H

#include <memory>
#include <vector>
#include "../core/Updatable.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../../../../../common_base/constants.h"
#include "FragmentsInfo.h"
#include "../../../../../common_base/Game/ProjectileTypeDto.h"

class ProjectileInfo {
public:
    float shot_angle;
    char facing_sign;
    float max_damage;
    float explosion_radius;
    float power;
    float origin_x;
    float origin_y;
    float projectile_radius;
    bool affected_by_wind;
    int countdown;
    ProjectileTypeDto projectile_type;
    std::unique_ptr<FragmentsInfo> fragment_info;

    ProjectileInfo(
        float shot_angle,
        char facing_sign,
        float max_damage,
        float explosion_radius,
        float power,
        float origin_x,
        float origin_y,
        float projectile_radius,
        bool affected_by_wind,
        int countdown,
        ProjectileTypeDto projectile_type,
        std::unique_ptr<FragmentsInfo> fragment_info
    );

};


#endif

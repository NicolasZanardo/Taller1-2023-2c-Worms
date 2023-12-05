#ifndef TP_WORMS_PROJECTILEINFO_H
#define TP_WORMS_PROJECTILEINFO_H

#include <memory>
#include <vector>
#include "Updatable.h"
#include "WeaponTypeDto.h"
#include "constants.h"
#include "FragmentsInfo.h"
#include "ProjectileTypeDto.h"
#include "RotationStrategy.h"

class ProjectileInfo {
public:
    float shot_angle;
    char facing_sign;
    float max_damage;
    float explosion_radius;
    float power;
    float origin_x;
    float origin_y;
    bool affected_by_wind;
    int countdown;
    ProjectileTypeDto projectile_type;
    std::unique_ptr<FragmentsInfo> fragment_info;
    RotationType rotation_type;

    ProjectileInfo(
        float shot_angle,
        char facing_sign,
        float max_damage,
        float explosion_radius,
        float power,
        float origin_x,
        float origin_y,
        bool affected_by_wind,
        int countdown,
        ProjectileTypeDto projectile_type,
        std::unique_ptr<FragmentsInfo> fragment_info,
        RotationType rotation_type
    ) :
        shot_angle(shot_angle),
        facing_sign(facing_sign),
        max_damage(max_damage),
        explosion_radius(explosion_radius),
        power(power),
        origin_x(origin_x),
        origin_y(origin_y),
        affected_by_wind(affected_by_wind),
        countdown(countdown),
        projectile_type(projectile_type),
        fragment_info(std::move(fragment_info)),
        rotation_type(rotation_type) {}
};


#endif

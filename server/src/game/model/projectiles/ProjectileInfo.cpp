#include "ProjectileInfo.h"

ProjectileInfo::ProjectileInfo(
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
    WeaponTypeDto from_weapon
) :
    shot_angle(shot_angle),
    facing_sign(facing_sign),
    max_damage(max_damage),
    explosion_radius(explosion_radius),
    power(power),
    origin_x(origin_x),
    origin_y(origin_y),
    projectile_radius(projectile_radius),
    affected_by_wind(affected_by_wind),
    countdown(countdown),
    from_weapon(from_weapon) {}

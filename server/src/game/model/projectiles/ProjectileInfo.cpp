#include "ProjectileInfo.h"

ProjectileInfo::ProjectileInfo(
    size_t shooter_id,
    float shot_angle,
    char facing_sign,
    float damage,
    float explosion_radius,
    float power,
    float origin_x,
    float origin_y,
    WeaponTypeDto from_weapon
) :
    shooter_id(shooter_id),
    shot_angle(shot_angle),
    facing_sign(facing_sign),
    damage(damage),
    explosion_radius(explosion_radius),
    power(power),
    origin_x(origin_x),
    origin_y(origin_y),
    from_weapon(from_weapon) {}

#include "FragmentsInfo.h"

FragmentsInfo::FragmentsInfo(
    int amount,
    float max_damage,
    float explosion_radius,
    float fragment_radius,
    ProjectileTypeDto projectile_type
) :
    amount(amount), max_damage(max_damage), explosion_radius(explosion_radius),
    fragment_radius(fragment_radius), projectile_type(projectile_type) {}
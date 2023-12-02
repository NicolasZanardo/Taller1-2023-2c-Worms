#ifndef TP_WORMS_FRAGMENTSINFO_H
#define TP_WORMS_FRAGMENTSINFO_H

#include "ProjectileTypeDto.h"

class FragmentsInfo {
public:
    int amount;
    float max_damage;
    float explosion_radius;
    ProjectileTypeDto projectile_type;

    FragmentsInfo(
        int amount,
        float max_damage,
        float explosion_radius,
        ProjectileTypeDto projectile_type
    ) :
        amount(amount), max_damage(max_damage), explosion_radius(explosion_radius), projectile_type(projectile_type) {}

};



#endif

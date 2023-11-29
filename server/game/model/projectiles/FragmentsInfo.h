#ifndef TP_WORMS_FRAGMENTSINFO_H
#define TP_WORMS_FRAGMENTSINFO_H

#include "ProjectileTypeDto.h"

class FragmentsInfo {
public:
    int amount;
    float max_damage;
    float explosion_radius;
    float fragment_radius;
    ProjectileTypeDto projectile_type;

    FragmentsInfo(
        int amount,
        float max_damage,
        float explosion_radius,
        float fragment_radius,
        ProjectileTypeDto projectileTypeDto
    );

};



#endif

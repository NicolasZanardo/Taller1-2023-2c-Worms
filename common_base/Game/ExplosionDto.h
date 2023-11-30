#ifndef TP_WORMS_EXPLOSIONDTO_H
#define TP_WORMS_EXPLOSIONDTO_H

#include "ProjectileTypeDto.h"

struct ExplosionDto {
    ProjectileTypeDto projectile_type;
    float x;
    float y;
    float radius;

    ExplosionDto(
        ProjectileTypeDto projectile_type,
        float x,
        float y,
        float radius
    ) :
        projectile_type(projectile_type),
        x(x),
        y(y),
        radius(radius) {};
};

#endif //TP_WORMS_EXPLOSIONDTO_H

#ifndef TP_WORMS_PROJECTILEDTO_H
#define TP_WORMS_PROJECTILEDTO_H

#include "ProjectileTypeDto.h"

struct ProjectileDto {
    int entity_id;
    ProjectileTypeDto type;
    float x;
    float y;

    ProjectileDto(
        int entity_id,
        ProjectileTypeDto type,
        float x,
        float y
    ) :
        entity_id(entity_id),
        type(type),
        x(x), y(y) {}
};


#endif

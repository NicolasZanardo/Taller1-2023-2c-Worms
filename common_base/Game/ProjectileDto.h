#ifndef TP_WORMS_PROJECTILEDTO_H
#define TP_WORMS_PROJECTILEDTO_H

#include "ProjectileTypeDto.h"

struct ProjectileDto {
    int entity_id;
    ProjectileTypeDto type;
    float x;
    float y;
    bool spawned_facing_right;
    float angle;

    ProjectileDto(
        int entity_id,
        ProjectileTypeDto type,
        float x,
        float y,
        bool spawned_facing_right,
        float angle
    ) :
        entity_id(entity_id),
        type(type),
        x(x), y(y),
        spawned_facing_right(spawned_facing_right),
        angle(angle) {};
};

#endif

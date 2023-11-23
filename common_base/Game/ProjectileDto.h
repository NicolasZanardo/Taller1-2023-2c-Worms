#ifndef TP_WORMS_PROJECTILEDTO_H
#define TP_WORMS_PROJECTILEDTO_H

#include "WeaponTypeDto.h"

struct ProjectileDto {
    int entity_id;
    WeaponTypeDto from_weapon;
    float x;
    float y;

    ProjectileDto(
        int entity_id,
        WeaponTypeDto from_weapon,
        float x,
        float y
    ) :
        entity_id(entity_id),
        from_weapon(from_weapon),
        x(x), y(y) {}
};


#endif

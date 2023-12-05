#ifndef TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H
#define TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H

#include <string>
#include "Game/ProjectileTypeDto.h"

class ProjectileSpriteKeyMapper {
public:
    static std::string map(ProjectileTypeDto projectile);
};


#endif //TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H

#ifndef TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H
#define TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H

#include <string>
#include "Game/WeaponTypeDto.h"

class ProjectileSpriteKeyMapper {
public:
    static std::string map(WeaponTypeDto weapon);
};


#endif //TP_WORMS_PROJECTILE_SPRITE_KEY_MAPPER_H

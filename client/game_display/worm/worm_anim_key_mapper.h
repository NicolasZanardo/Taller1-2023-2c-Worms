#ifndef TP_WORMS_WORM_ANIM_KEY_MAPPER_H
#define TP_WORMS_WORM_ANIM_KEY_MAPPER_H


#include "Game/WeaponTypeDto.h"
#include "Game/wormDto.h"
#include "worm_anim_key.h"

class WormAnimKeyMapper {
public:
    static WormAnimKey get_anim_key(MovementStateDto movement_state, WeaponTypeDto weapon_hold);
};


#endif //TP_WORMS_WORM_ANIM_KEY_MAPPER_H

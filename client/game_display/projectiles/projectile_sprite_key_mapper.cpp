#include "projectile_sprite_key_mapper.h"
#include "sprite_keys.h"

std::string ProjectileSpriteKeyMapper::map(WeaponTypeDto weapon) {
    switch (weapon) {
        case WeaponTypeDto::BAZOOKA:
            return P_BAZOOKA;
        case WeaponTypeDto::MORTAR:
            return P_MORTAR;
        case WeaponTypeDto::GREEN_GRENADE:
            return P_GREEN_GRENADE;
    }
}

#include "worm_anim_key_mapper.h"

WormAnimKey WormAnimKeyMapper::get_anim_key(MovementStateDto movement_state, WeaponTypeDto weapon_hold) {
    switch (movement_state) {

        case MovementStateDto::MOVING: {
            return WormAnimKey::MOVING;
        }

        case MovementStateDto::IDLE: {
            switch (weapon_hold) {
                case WeaponTypeDto::NONE:
                    return WormAnimKey::IDLE;
                case WeaponTypeDto::BAZOOKA:
                    return WormAnimKey::IDLE_BAZOOKA;
                case WeaponTypeDto::MORTAR:
                    return WormAnimKey::IDLE_MORTAR;
                case WeaponTypeDto::GREEN_GRENADE:
                    return WormAnimKey::IDLE_GREEN_GRENADE;
                default:
                    return WormAnimKey::IDLE;
            }
        }

        case MovementStateDto::GOING_UPWARDS: {
            switch (weapon_hold) {
                case WeaponTypeDto::NONE:
                    return WormAnimKey::JUMPING;
                case WeaponTypeDto::BAZOOKA:
                    return WormAnimKey::JUMPING_BAZOOKA;
                case WeaponTypeDto::MORTAR:
                    return WormAnimKey::JUMPING_MORTAR;
                case WeaponTypeDto::GREEN_GRENADE:
                    return WormAnimKey::JUMPING_GREEN_GRENADE;
                default:
                    return WormAnimKey::JUMPING;
            }
        }

        case MovementStateDto::FALLING: {
            switch (weapon_hold) {
                case WeaponTypeDto::NONE:
                    return WormAnimKey::FALLING;
                case WeaponTypeDto::BAZOOKA:
                    return WormAnimKey::FALLING_BAZOOKA;
                case WeaponTypeDto::MORTAR:
                    return WormAnimKey::FALLING_MORTAR;
                case WeaponTypeDto::GREEN_GRENADE:
                    return WormAnimKey::FALLING_GREEN_GRENADE;
                default:
                    return WormAnimKey::FALLING;
            }
        }
    }
}

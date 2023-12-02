#include "projectile_sprite_key_mapper.h"
#include "sprite_keys.h"

std::string ProjectileSpriteKeyMapper::map(ProjectileTypeDto projectile) {
    switch (projectile) {
        case ProjectileTypeDto::BAZOOKA:
            return P_BAZOOKA;
        case ProjectileTypeDto::MORTAR:
            return P_MORTAR;
        case ProjectileTypeDto::MORTAR_FRAGMENT:
            return P_MORTAR;
        case ProjectileTypeDto::GREEN_GRENADE:
            return P_GREEN_GRENADE;
        case ProjectileTypeDto::HOLY_GRENADE:
            return P_HGRENADE;
        case ProjectileTypeDto::DYNAMITE:
            return P_DYNAMITE;
        case ProjectileTypeDto::FRAGMENT:
            return P_FRAGMENT;
        default:
            return P_BAZOOKA;
    }
}

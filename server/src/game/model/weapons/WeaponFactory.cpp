#include "WeaponFactory.h"
#include "chargeable_weapons/Bazooka.h"
#include "chargeable_weapons/Mortar.h"
#include "chargeable_weapons/GreenGrenade.h"

std::shared_ptr<Weapon> WeaponFactory::create(WeaponCfg &weapon_cfg) {

    switch (weapon_cfg.type) {
        case WeaponTypeDto::NONE:
            break;
        case WeaponTypeDto::BAZOOKA:
            return std::make_shared<Bazooka>(weapon_cfg);
        case WeaponTypeDto::MORTAR:
            return std::make_shared<Mortar>(weapon_cfg);
        case WeaponTypeDto::GREEN_GRENADE:
            return std::make_shared<GreenGrenade>(weapon_cfg);
        case WeaponTypeDto::SAINT_GRENADE:
            break;
        case WeaponTypeDto::BASEBALL_BAT:
            break;
        case WeaponTypeDto::RED_GRENADE:
            break;
        case WeaponTypeDto::BANANA:
            break;
        case WeaponTypeDto::AIRSTRIKE:
            break;
        case WeaponTypeDto::TELEPORTATION:
            break;
    }
    // TODO FOR NOW THROW ERROR THEN CAN HANDLE WITH NULLPTR
    throw std::runtime_error("Unimplemented Weapon constructor");
    return nullptr;
}

#ifndef TP_WORMS_WEAPON_CFG_H
#define TP_WORMS_WEAPON_CFG_H

#include "WeaponTypeDto.h"

struct WeaponCfg {
    WeaponTypeDto type;
    int ammo;
    float max_damage;
    float explosion_radius;
    float max_shoot_power;
    int default_projectile_countdown; // Milliseconds
    float projectile_radius;
    bool affected_by_wind;
};

#endif

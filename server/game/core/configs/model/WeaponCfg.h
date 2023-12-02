#ifndef TP_WORMS_WEAPON_CFG_H
#define TP_WORMS_WEAPON_CFG_H

#include <optional>
#include "WeaponTypeDto.h"
#include "ProjectileDto.h"
#include "RotationStrategy.h"


struct FragmentsCfg {
    int amount;
    float max_damage;
    float explosion_radius;
    bool affected_by_wind;
};

struct ProjectileCfg {
    ProjectileTypeDto type;
    float max_damage;
    float explosion_radius;
    bool affected_by_wind;
    RotationType rotation;
    int default_explosion_countdown;
    std::optional<FragmentsCfg> fragments;
};

struct ChargeCfg {
    int time_to_charge;
    float initial_charged_percentage;
};

struct WeaponCfg {
    WeaponTypeDto type;
    ProjectileCfg projectile;
    int ammo;
    float shoot_power;
    std::optional<ChargeCfg> charge;
};

#endif

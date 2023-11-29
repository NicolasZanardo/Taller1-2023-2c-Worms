#include "InstantWeaponExample.h"
#include <iostream>

InstantWeaponExample::InstantWeaponExample(WeaponCfg &cfg) : InstantShotWeapon(cfg) {}

std::unique_ptr<CShot> InstantWeaponExample::shoot(float from_x, float from_y, char facing_sign) {
    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            max_damage,
            explosion_radius,
            max_shoot_power,
            from_x,
            from_y,
            projectile_radius,
            affected_by_wind,
            -1, // TODO not using from cfg for noew
            ProjectileTypeDto::GREEN_GRENADE,
            nullptr
        )
    );
}

bool InstantWeaponExample::change_projectile_count_down(ProjectileCountDown time) {
    return false;
}

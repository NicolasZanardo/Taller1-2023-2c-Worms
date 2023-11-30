#include "Bazooka.h"
#include <iostream>

Bazooka::Bazooka(WeaponCfg &weapon_cfg) : ChargeableWeapon(weapon_cfg){}

bool Bazooka::change_projectile_count_down(ProjectileCountDown time) { return false; }

std::unique_ptr<CShot> Bazooka::shoot(float charged_power, float from_x, float from_y, char facing_sign) {
    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            max_damage,
            explosion_radius,
            max_shoot_power * charged_power,
            from_x,
            from_y,
            projectile_radius,
            affected_by_wind,
            -1,
            ProjectileTypeDto::BAZOOKA,
            nullptr,
            RotationType::VelocityAligned
        )
    );
}

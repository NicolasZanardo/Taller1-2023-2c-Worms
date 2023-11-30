#include "Mortar.h"
#include <iostream>

Mortar::Mortar(WeaponCfg &weapon_cfg) : ChargeableWeapon(weapon_cfg) {}

bool Mortar::change_projectile_count_down(ProjectileCountDown time) { return false; }

std::unique_ptr<CShot> Mortar::shoot(float charged_power, float from_x, float from_y, char facing_sign) {
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
            -1, //TODO not using cfg.projectile_countdown for now
            ProjectileTypeDto::MORTAR,
            std::make_unique<FragmentsInfo>(
                6,
                10,
                2,
                FRAGMENT_RADIUS,
                ProjectileTypeDto::FRAGMENT
            ),
            RotationType::VelocityAligned
        )
    );
}


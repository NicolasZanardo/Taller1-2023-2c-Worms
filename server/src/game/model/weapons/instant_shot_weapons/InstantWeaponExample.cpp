#include "InstantWeaponExample.h"
#include <iostream>

InstantWeaponExample::InstantWeaponExample(
    const int ammo_left,
    const float max_damage,
    const float explosion_radius,
    const int default_count_down_time,
    const float shoot_power
) : InstantShotWeapon(
    ammo_left,
    max_damage,
    explosion_radius,
    WeaponTypeDto::GREEN_GRENADE
),
    projectile_countdown(default_count_down_time),
    default_projectile_countdown(default_count_down_time),
    shoot_power(shoot_power) {}

std::unique_ptr<CShot> InstantWeaponExample::shoot(float from_x, float from_y, char facing_sign) {
    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            max_damage,
            explosion_radius,
            shoot_power,
            from_x,
            from_y,
            PROJECTILE_RADIUS,
            true,
            projectile_countdown,
            ProjectileTypeDto::GREEN_GRENADE,
            nullptr
        )
    );
}

bool InstantWeaponExample::change_projectile_count_down(ProjectileCountDown time) {
    projectile_countdown = static_cast<int>(time);
    return true;
}

void InstantWeaponExample::on_turn_ended() {
    Weapon::on_turn_ended();
    projectile_countdown = default_projectile_countdown;
}

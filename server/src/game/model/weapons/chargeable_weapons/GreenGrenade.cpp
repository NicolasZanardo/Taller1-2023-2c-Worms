#include "GreenGrenade.h"
#include <iostream>

GreenGrenade::GreenGrenade(
    const int ammo_left,
    const float max_damage,
    const float explosion_radius,
    const int default_count_down_time,
    const float max_shoot_power
) : ChargeableWeapon(
    ammo_left,
    max_damage,
    explosion_radius,
    WeaponTypeDto::GREEN_GRENADE
),
    projectile_countdown(default_count_down_time),
    default_projectile_countdown(default_count_down_time),
    max_shoot_power(max_shoot_power) {}

std::unique_ptr<CShot> GreenGrenade::shoot(float charged_power, float from_x, float from_y, char facing_sign) {
    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            max_damage,
            explosion_radius,
            charged_power * max_shoot_power,
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

bool GreenGrenade::change_projectile_count_down(ProjectileCountDown time) {
    projectile_countdown = static_cast<int>(time);
    return true;
}

void GreenGrenade::on_turn_ended() {
    ChargeableWeapon::on_turn_ended();
    projectile_countdown = default_projectile_countdown;
}

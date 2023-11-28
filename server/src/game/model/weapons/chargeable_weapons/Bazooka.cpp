#include "Bazooka.h"
#include <iostream>

Bazooka::Bazooka(
    int ammo_left,
    float damage,
    float explosion_radius
) : ChargeableWeapon(
    ammo_left,
    damage,
    explosion_radius,
    WeaponTypeDto::BAZOOKA
) {}

void Bazooka::end_shooting(float from_x, float from_y, char facing_sign) {
    // TODO If holds the shot from a previous turn and then releases the shot key calling an end shooting directly
    // without a previous start_shooting
    has_shot_this_turn = true;
    --ammo_left;
    c_shot = std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.aimed_angle,
            facing_sign,
            max_damage,
            explosion_radius,
            max_power,
            from_x,
            from_y,
            PROJECTILE_RADIUS,
            true,
            -1,
            ProjectileTypeDto::BAZOOKA,
            nullptr
        )
    );
}

void

bool Bazooka::change_projectile_count_down(ProjectileCountDown time) {
    // Cant change projectile countdown
    // TODO could return feedback to client in the future
    return false;
}

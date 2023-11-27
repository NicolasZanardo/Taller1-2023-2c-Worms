#include "Bazooka.h"
#include <iostream>

Bazooka::Bazooka(
    int ammo_left,
    float damage,
    float explosion_radius
) : Weapon(
    ammo_left,
    damage,
    11,
    explosion_radius,
    WeaponTypeDto::BAZOOKA
) {}

void Bazooka::start_shooting(float from_x, float from_y, char facing_sign) {
    if (!has_shot_this_turn && ammo_left > 0) {
        has_shot_this_turn = true;
        --ammo_left;
        // std::cout << "Bazooka has " << ammo_left << " ammo left\n";
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
                type
            )
        );
    } else {
        // std::cout << "Cant shoot again this turn\n";
    }
}

void Bazooka::end_shooting(float from_x, float from_y, char facing_sign) {}

bool Bazooka::change_projectile_count_down(ProjectileCountDown time) {
    // Cant change projectile countdown
    // TODO could return feedback to client in the future
    return false;
}

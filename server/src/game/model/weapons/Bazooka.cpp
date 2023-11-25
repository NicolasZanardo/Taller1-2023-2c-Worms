#include "Bazooka.h"
#include <iostream>

Bazooka::Bazooka(
    size_t owner_id,
    int ammo_left,
    float damage,
    float explosion_radius
) : Weapon(
    owner_id,
    ammo_left,
    damage,
    11,
    explosion_radius,
    WeaponTypeDto::BAZOOKA
) {}

void Bazooka::start_shooting(float from_x, float from_y, char facing_sign) {
    if (!has_shot_this_turn) {
        has_shot_this_turn = true;
        --ammo_left;
        // std::cout << "Bazooka has " << ammo_left << " ammo left\n";
        c_shot = std::make_unique<CShot>(
            std::make_unique<ProjectileInfo>(
                owner_id,
                rotation.aimed_angle,
                facing_sign,
                damage,
                max_power,
                from_x,
                from_y,
                type
            )
        );
    } else {
        // std::cout << "Cant shoot again this turn\n";
    }
}

void Bazooka::end_shooting(float from_x, float from_y, char facing_sign) {}
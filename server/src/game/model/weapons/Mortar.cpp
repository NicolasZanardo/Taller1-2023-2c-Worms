#include "Mortar.h"
#include <iostream>

// TODO For now same logic as bazooka
Mortar::Mortar(
    size_t owner_id,
    int ammo_left,
    float damage,
    float explosion_radius
) : Weapon(
    owner_id,
    ammo_left,
    damage,
    10,
    explosion_radius,
    WeaponTypeDto::MORTAR
) {}

void Mortar::start_shooting(float from_x, float from_y, char facing_direction) {
    if (!has_shot_this_turn && ammo_left > 0) {
        has_shot_this_turn = true;
        --ammo_left;
        std::cout << "Mortar has " << ammo_left << " ammo left\n";
        c_shot = std::make_unique<CShot>(
            std::make_unique<ProjectileInfo>(
                owner_id,
                rotation.aimed_angle,
                facing_direction,
                damage,
                explosion_radius,
                max_power,
                from_x,
                from_y,
                type
            )
        );
    } else {
        std::cout << "Cant shot Mortar again\n";
    }
}

void Mortar::end_shooting(float from_x, float from_y, char facing_direction) {}
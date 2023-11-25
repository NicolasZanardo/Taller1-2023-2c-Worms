#include "GreenGrenade.h"
#include <iostream>

// TODO For now same logic as bazooka
GreenGrenade::GreenGrenade(
    size_t owner_id,
    int ammo_left,
    float damage,
    float explosion_radius
) : Weapon(
    owner_id,
    ammo_left,
    damage,
    5,
    explosion_radius,
    WeaponTypeDto::GREEN_GRENADE
) {}

void GreenGrenade::start_shooting(float from_x, float from_y, char facing_direction) {
    if (!has_shot_this_turn) {
        has_shot_this_turn = true;
        --ammo_left;
        // std::cout << "Green grenade has " << ammo_left << " ammo left\n";
        c_shot = std::make_unique<CShot>(
            std::make_unique<ProjectileInfo>(
                owner_id,
                rotation.aimed_angle,
                facing_direction,
                damage,
                max_power,
                from_x,
                from_y,
                type
            )
        );
    } else {
        // std::cout << "Cant shot green grenade again\n";
    }
}

void GreenGrenade::end_shooting(float from_x, float from_y, char facing_direction) {
}
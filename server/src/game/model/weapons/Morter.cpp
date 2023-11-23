#include "Morter.h"
#include <iostream>

// TODO For now same logic as bazooka
Morter::Morter(int ammo_left, Damage damage) : Weapon(ammo_left, damage, 100, WeaponTypeDto::MORTER) {}

void Morter::start_shooting(float from_x, float from_y) {
    if (!has_shot_this_turn) {
        has_shot_this_turn = true;
        --ammo_left;
        std::cout << "Morter has " << ammo_left << " ammo left\n";
        c_shot = std::make_unique<Shot>(
            std::make_shared<ProjectileInfo>(
                damage,
                shoot_power,
                from_x,
                from_y,
                type
            ),
            rotation.aimed_angle
        );
    } else {
        std::cout << "Cant shot Morter again\n";
    }
}

void Morter::end_shooting(float from_x, float from_y) {}
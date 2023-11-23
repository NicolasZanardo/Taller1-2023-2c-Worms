#include "GreenGrenade.h"
#include <iostream>

// TODO For now same logic as bazooka
GreenGrenade::GreenGrenade(int ammo_left, Damage damage) : Weapon(ammo_left, damage, 100, WeaponTypeDto::GREEN_GRENADE) {}

void GreenGrenade::start_shooting(float from_x, float from_y) {
    if (!has_shot_this_turn) {
        has_shot_this_turn = true;
        --ammo_left;
        std::cout << "Green grenade has " << ammo_left << " ammo left\n";
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
        std::cout << "Cant shot green grenade again\n";
    }
}

void GreenGrenade::end_shooting(float from_x, float from_y) {
}
#include "Bazooka.h"
#include <iostream>

Bazooka::Bazooka(
    int ammo_left,
    float damage,
    float explosion_radius
    ) : Weapon(
        ammo_left,
        damage,
        explosion_radius,
        100,
        WeaponTypeDto::BAZOOKA
        ) {}

void Bazooka::start_shooting(float from_x, float from_y) {
    if (!has_shot_this_turn) {
        has_shot_this_turn = true;
        --ammo_left;
        std::cout << "Bazooka has " << ammo_left << " ammo left\n";
        c_shot = std::make_unique<CShot>(
            std::make_unique<ProjectileInfo>(
                damage,
                shoot_power,
                from_x,
                from_y,
                type
            ),
            rotation.aimed_angle
        );
    } else {
        std::cout << "Cant shoot again this turn\n";
    }
}

void Bazooka::end_shooting(float from_x, float from_y) {}
#include "Mortar.h"
#include <iostream>

Mortar::Mortar(
    int ammo_left,
    float damage,
    float explosion_radius
) : Weapon(
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
                rotation.aimed_angle,
                facing_direction,
                max_damage,
                explosion_radius,
                max_power,
                from_x,
                from_y,
                PROJECTILE_RADIUS,
                true,
                -1,
                ProjectileTypeDto::MORTAR,
                std::make_unique<FragmentsInfo>(
                    6,
                    10,
                    2,
                    FRAGMENT_RADIUS,
                    ProjectileTypeDto::MORTAR_FRAGMENT
                    )
            )
        );
    } else {
        std::cout << "Cant shot Mortar again\n";
    }
}

void Mortar::end_shooting(float from_x, float from_y, char facing_direction) {}

bool Mortar::change_projectile_count_down(ProjectileCountDown time) {
    return false;
}

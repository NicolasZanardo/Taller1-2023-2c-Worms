#include "GreenGrenade.h"
#include <iostream>

// TODO For now same logic as bazooka
GreenGrenade::GreenGrenade(
    int ammo_left,
    float max_damage,
    float explosion_radius,
    int default_count_down_time
) : Weapon(
    ammo_left,
    max_damage,
    5,
    explosion_radius,
    WeaponTypeDto::GREEN_GRENADE
),
    projectile_countdown(default_count_down_time),
    default_projectile_countdown(default_count_down_time) {}

void GreenGrenade::start_shooting(float from_x, float from_y, char facing_direction) {
    if (!has_shot_this_turn && ammo_left > 0) {
        has_shot_this_turn = true;
        --ammo_left;
        std::cout << "Projectile countdown is " << projectile_countdown << " ammo left\n";
        c_shot = std::make_unique<CShot>(
            std::make_unique<ProjectileInfo>(
                rotation.aimed_angle,
                facing_direction,
                max_damage,
                explosion_radius,
                max_power,
                from_x,
                from_y,
                PROJECTILE_RADIUS, // TODO For each weapon can change the projectile radius
                true,
                projectile_countdown,
                type
            )

        );
    } else {
        // std::cout << "Cant shot green grenade again\n";
    }
}

void GreenGrenade::end_shooting(float from_x, float from_y, char facing_direction) {
}


bool GreenGrenade::change_projectile_count_down(ProjectileCountDown time) {
    projectile_countdown = static_cast<int>(time);
    return true;
}

void GreenGrenade::on_turn_ended() {
    Weapon::on_turn_ended();
    projectile_countdown = default_projectile_countdown;
}

#include "Weapon.h"
#include <iostream>
Weapon::Weapon(WeaponCfg &weapon_data, std::unique_ptr<ProjectileCountDownChanger> countdown_changer) :
    projectile_data(weapon_data.projectile),
    type(weapon_data.type), ammo_left(weapon_data.ammo),
    max_shoot_power(weapon_data.shoot_power),
    has_shot_this_turn(false),
    rotation(),
    countdown_changer(std::move(countdown_changer)),
    c_shot(nullptr) {}

void Weapon::start_aiming_up() {
    rotation.start_aiming_up();
}

void Weapon::start_aiming_down() {
    rotation.start_aiming_down();
}

void Weapon::stop_aiming_up() {
    rotation.stop_aiming_up();
}

void Weapon::stop_aiming_down() {
    rotation.stop_aiming_down();
}

void Weapon::on_update(const int it, const int rate) {
    rotation.on_update();
}

void Weapon::on_turn_ended() {
    rotation.on_turn_ended();
    has_shot_this_turn = false;
}

void Weapon::change_projectile_count_down(ProjectileCountDown count_down) {
    if (countdown_changer) {
        countdown_changer->change_countdown(static_cast<int>(count_down));
    }
}

std::unique_ptr<CShot> Weapon::shot_component() {
    return std::move(c_shot);
}

WeaponTypeDto Weapon::WeaponType() {
    return type;
}

float Weapon::AimedAngle() const {
    return rotation.get_angle();
}

std::unique_ptr<CShot> Weapon::shoot(float from_x, float from_y, char facing_sign) {
    std::unique_ptr<FragmentsInfo> fragments = nullptr;
    if (projectile_data.fragments) {
        fragments = std::make_unique<FragmentsInfo>(
            projectile_data.fragments->amount,
            projectile_data.fragments->max_damage,
            projectile_data.fragments->explosion_radius,
            ProjectileTypeDto::FRAGMENT
        );
    }

    int explosion_countdown = 0;

    if (countdown_changer) {
        explosion_countdown = countdown_changer->get_projectile_countdown();
    }

    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            projectile_data.max_damage,
            projectile_data.explosion_radius,
            max_shoot_power,
            from_x,
            from_y,
            projectile_data.affected_by_wind,
            explosion_countdown,
            projectile_data.type,
            std::move(fragments),
            projectile_data.rotation
        )
    );
}

void Weapon::upgrade(int ammo, float damage) {
    projectile_data.max_damage = damage;
    ammo_left = ammo;
}

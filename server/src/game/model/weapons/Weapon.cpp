#include "Weapon.h"

Weapon::Weapon(WeaponCfg &cfg) :
    type(cfg.type), ammo_left(cfg.ammo), max_damage(cfg.max_damage),
    max_shoot_power(cfg.max_shoot_power), explosion_radius(cfg.explosion_radius),
    projectile_radius(cfg.projectile_radius),
    affected_by_wind(cfg.affected_by_wind),
    has_shot_this_turn(false),
    rotation(),
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

std::unique_ptr<CShot> Weapon::shot_component() {
    return std::move(c_shot);
}

WeaponTypeDto Weapon::WeaponType() {
    return type;
}

float Weapon::AimedAngle() const {
    return rotation.get_angle();
}


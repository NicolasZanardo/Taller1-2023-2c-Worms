#include "Weapon.h"

Weapon::Weapon(
    size_t owner_id,
    int ammo_left,
    float damage,
    float max_power,
    float explosion_radius,
    WeaponTypeDto type
) :
    owner_id(owner_id), type(type), ammo_left(ammo_left), damage(damage, explosion_radius), charged_power(0), max_power(max_power),
    has_shot_this_turn(false), rotation(),
    c_shot(nullptr) {
}

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

void Weapon::on_update() {
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
    return rotation.aimed_angle;
}

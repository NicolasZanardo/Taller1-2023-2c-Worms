#include "Weapon.h"

Weapon::Weapon(int ammo_left, Damage damage, float shoot_power, WeaponTypeDto type) :
    type(type), ammo_left(ammo_left), damage(damage), shoot_power(shoot_power), has_shot_this_turn(false), rotation(),
    c_shot(nullptr) {
    // TODO assert shoot power between 0 and 100
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

std::unique_ptr<Shot> Weapon::shot_component() {
    return std::move(c_shot);
}
#include "Weapon.h"

Weapon::Weapon() :
        ammo_left(0), shoot_power(0) ,weapon_rotation() {}

void Weapon::start_aiming_up() {
    weapon_rotation.start_aiming_up();
}

void Weapon::start_aiming_down() {
    weapon_rotation.start_aiming_down();
}

void Weapon::stop_aiming_up() {
    weapon_rotation.stop_aiming_up();
}

void Weapon::stop_aiming_down() {
    weapon_rotation.stop_aiming_down();
}

void Weapon::on_update() {
    weapon_rotation.on_update();
}

void Weapon::on_reset() {
    weapon_rotation.on_reset();
}

void Weapon::shoot() {
    // TODO()
}




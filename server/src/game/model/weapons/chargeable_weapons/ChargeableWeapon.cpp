#include "ChargeableWeapon.h"
#include <iostream>
/* Cant be instantiated protected constructor
 *
 * Subclasses of ChargeableWeapon
 * only need to generate the shot based on the
 * charge_power member
 */

ChargeableWeapon::ChargeableWeapon(
    int ammo_left,
    float damage,
    float explosion_radius,
    WeaponTypeDto type
) : Weapon(
    ammo_left,
    damage,
    explosion_radius,
    type
), charged_power(0), is_charging(false), started_charge_at_x(0), started_charge_at_y(0), facing_sign_when_started_charge(1) {}

void ChargeableWeapon::start_shooting(float from_x, float from_y, char facing_sign) {
    if (!has_shot_this_turn && ammo_left > 0) {
        is_charging = true;
        started_charge_at_x = from_x;
        started_charge_at_y = from_y;
        facing_sign_when_started_charge = facing_sign;
    }
}

void ChargeableWeapon::on_update(const int it, const int rate) {
    Weapon::on_update(it, rate);
    if (is_charging && charged_power < MAX_POWER) {
        float charging_increment = static_cast<float>(it * rate) / CHARGING_DURATION;
        charged_power += charging_increment;
        // std::cout << "Charged power is: " << charged_power <<"\n";
        if (charged_power >= MAX_POWER) {
            charged_power = MAX_POWER;
            end_shooting(started_charge_at_x, started_charge_at_y, facing_sign_when_started_charge);
        }
    }
}

void ChargeableWeapon::end_shooting(float from_x, float from_y, char facing_sign) {
    if (is_charging) {
        c_shot = shoot(charged_power, from_x, from_y, facing_sign);
        has_shot_this_turn = true;
        is_charging = false;
        charged_power = 0;
    }
}

void ChargeableWeapon::on_turn_ended() {
    Weapon::on_turn_ended();
    charged_power = 0;
}



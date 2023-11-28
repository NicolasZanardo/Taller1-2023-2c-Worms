#include "ChargeableWeapon.h"

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
    if (is_charging && charged_power < 1.0) {
        float charging_increment = static_cast<float>(it * rate) / charging_duration;
        charged_power += charging_increment;
        if (charged_power >= 1.0) {
            charged_power = 1.0;
            end_shooting(started_charge_at_x, started_charge_at_y, facing_sign_when_started_charge);
        }
    }
}

void ChargeableWeapon::end_shooting(float from_x, float from_y, char facing_sign) {
    if (is_charging) {
        on_end_shooting(from_x, from_y, facing_sign);
        is_charging = false;
    }
}

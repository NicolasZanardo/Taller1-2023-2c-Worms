#include "ChargeableWeapon.h"
#include "Logger.h"
#include <iostream>

/* Cant be instantiated protected constructor
 *
 * Subclasses of ChargeableWeapon
 * only need to generate the shot based on the
 * charge_power member
 */
ChargeableWeapon::ChargeableWeapon(WeaponCfg &cfg, std::unique_ptr<ProjectileCountDownChanger> projectile_countdown_changer) :
    Weapon(cfg, std::move(projectile_countdown_changer)),
    time_to_fully_charge(cfg.charge->time_to_charge),
    charged_percentage(cfg.charge->initial_charged_percentage),
    is_charging(false),
    started_charge_at_x(0),
    started_charge_at_y(0),
    facing_sign_when_started_charge(1) {}


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
    if (is_charging && charged_percentage < MAX_POWER) {
        float charging_increment = static_cast<float>(it * rate) / time_to_fully_charge;
        charged_percentage += charging_increment;
        if (charged_percentage >= MAX_POWER) {
            charged_percentage = MAX_POWER;
            end_shooting(started_charge_at_x, started_charge_at_y, facing_sign_when_started_charge);
        }
    }
}
// todo control movement while charging
void ChargeableWeapon::end_shooting(float from_x, float from_y, char facing_sign) {
    if (is_charging) {
        c_shot = shoot(from_x, from_y, facing_sign);
        has_shot_this_turn = true;
        is_charging = false;
        charged_percentage = 0;
    }
}

void ChargeableWeapon::on_turn_ended() {
    Weapon::on_turn_ended();
    charged_percentage = 0;
}

std::unique_ptr<CShot> ChargeableWeapon::shoot(float from_x, float from_y, char facing_sign) {
    auto shot = Weapon::shoot(from_x, from_y, facing_sign);
    for (auto &projectile: shot->Projectiles()) {
        projectile->power *= charged_percentage;
    }
    return shot; // MOVE?
}



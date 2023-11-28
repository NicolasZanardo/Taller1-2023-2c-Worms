#include "InstantShotWeapon.h"

InstantShotWeapon::InstantShotWeapon(WeaponCfg &cfg) : Weapon(cfg) {}

void InstantShotWeapon::start_shooting(float from_x, float from_y, char facing_sign) {
    if (!has_shot_this_turn && ammo_left > 0) {
        has_shot_this_turn = true;
        --ammo_left;
        c_shot = shoot(from_x, from_y, facing_sign);
    }
}

void InstantShotWeapon::end_shooting(float from_x, float from_y, char facing_sign) {}

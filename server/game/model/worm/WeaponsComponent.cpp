#include "WeaponsComponent.h"
#include "WeaponFactory.h"
#include "Config.h"
#include <iostream>

WeaponsComponent::WeaponsComponent(Config<WeaponCfg> &weapons_cfg) :
    weapons(create_default_weapons(weapons_cfg)), actual_weapon(weapons.at(WeaponTypeDto::BAZOOKA)) {}

WeaponMap WeaponsComponent::create_default_weapons(Config<WeaponCfg> &weapons_cfg) {
    WeaponMap default_weapons;
    for (auto [cfg_id, weapon_cfg]: weapons_cfg) {
        default_weapons[weapon_cfg.type] = WeaponFactory::create(weapon_cfg);
    }
    return default_weapons;
}

void WeaponsComponent::update(const int it, const int rate) {
    if (actual_weapon) {
        actual_weapon->on_update(it, rate);
    }
}

void WeaponsComponent::on_turn_ended() {
    if (actual_weapon) {
        actual_weapon->on_turn_ended();
        auto it = weapons.find(WeaponTypeDto::BAZOOKA);
        if (it != weapons.end()) {
            actual_weapon = it->second;
        } else {
        }
    }
}

WeaponTypeDto WeaponsComponent::WeaponType() const {
    return actual_weapon->WeaponType();
}

float WeaponsComponent::AimedAngle() const {
    if (actual_weapon) {
        return actual_weapon->AimedAngle();
    }
}

void WeaponsComponent::start_aiming_down() {
    if (actual_weapon) {
        actual_weapon->start_aiming_down();
    }
}

void WeaponsComponent::start_aiming_up() {
    if (actual_weapon) {
        actual_weapon->start_aiming_up();
    }
}

void WeaponsComponent::stop_aiming_up() {
    if (actual_weapon) {
        actual_weapon->stop_aiming_up();
    }
}

void WeaponsComponent::stop_aiming_down() {
    if (actual_weapon) {
        actual_weapon->stop_aiming_down();
    }
}

void WeaponsComponent::do_weapon_primary_action(float from_x, float from_y, char facing_sign) {
    if (actual_weapon) {
        actual_weapon->start_shooting(from_x, from_y, facing_sign);
    }
}

void WeaponsComponent::do_weapon_secondary_action(float from_x, float from_y, char facing_sign) {
    if (actual_weapon) {
        actual_weapon->end_shooting(from_x, from_y, facing_sign);
    }
}

void WeaponsComponent::change_weapon(WeaponTypeDto weapon) {
    auto it = weapons.find(weapon);
    if (it != weapons.end()) {
        actual_weapon = it->second;
    } else {
        std::cout << "Weapon not found in weapons map\n";
    }
}

void WeaponsComponent::change_projectile_count_down(ProjectileCountDown count_down) {
    if (actual_weapon) {
        actual_weapon->change_projectile_count_down(count_down);
    }
}

std::unique_ptr<CShot> WeaponsComponent::shot_component() {
    auto c_shot = actual_weapon->shot_component();
    return c_shot;
}
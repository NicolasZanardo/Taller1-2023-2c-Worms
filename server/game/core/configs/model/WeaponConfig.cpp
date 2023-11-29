#include <iostream>
#include "Config.h"
#include "WeaponCfg.h"

#define WEAPONS_CFG_NAME "weapons.yaml"
#define WEAPONS_CFG_PATH CONFIGS_FILE_PATH WEAPONS_CFG_NAME

const std::unordered_map<std::string, WeaponTypeDto> TYPE_MAPPING = {
    {"bazooka", WeaponTypeDto::BAZOOKA},
    {"mortar", WeaponTypeDto::MORTAR},
    {"green_grenade", WeaponTypeDto::GREEN_GRENADE},
};

WeaponTypeDto string_to_weapon_type(const std::string& type_str) {
    auto it = TYPE_MAPPING.find(type_str);
    if (it != TYPE_MAPPING.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown weapon type: " + type_str);
    }
}

template<>
void Config<WeaponCfg>::parse_file() {
    try {
        YAML::Node main_node = YAML::LoadFile(WEAPONS_CFG_PATH);
        for (const auto &entry : main_node) {
            auto id = entry.first.as<int>();
            WeaponCfg weaponCfg;
            weaponCfg.type = string_to_weapon_type(entry.second["type"].as<std::string>());
            weaponCfg.ammo = entry.second["ammo"].as<int>();
            weaponCfg.max_damage = entry.second["max_damage"].as<float>();
            weaponCfg.explosion_radius = entry.second["explosion_radius"].as<float>();
            weaponCfg.max_shoot_power = entry.second["max_shoot_power"].as<float>();
            weaponCfg.default_projectile_countdown = entry.second["default_projectile_countdown"].as<int>();
            weaponCfg.projectile_radius = entry.second["projectile_radius"].as<float>();
            weaponCfg.affected_by_wind = entry.second["affected_by_wind"].as<bool>();

            config.emplace(id, weaponCfg);
        }
    } catch (const YAML::Exception& e) {
        std::cerr << "YAML parsing error: " << e.what() << " on WeaponConfig.cpp" << std::endl;
        throw (e);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        throw (e);
    }
}

#include <iostream>
#include "Config.h"
#include "WeaponCfg.h"
#include "ProjectileTypeDto.h"
#include "RotationStrategy.h"

#define WEAPONS_CFG_NAME "weapons.yaml"
#define PROJECTILES_CFG_NAME "projectiles.yaml"
#define WEAPONS_CFG_PATH CONFIGS_FILE_PATH WEAPONS_CFG_NAME
#define PROJECTILES_CFG_PATH CONFIGS_FILE_PATH PROJECTILES_CFG_NAME


const std::unordered_map<std::string, WeaponTypeDto> TYPE_MAPPING = {
    {"BAZOOKA",       WeaponTypeDto::BAZOOKA},
    {"MORTAR",        WeaponTypeDto::MORTAR},
    {"GREEN_GRENADE", WeaponTypeDto::GREEN_GRENADE},
    {"HOLY_GRENADE",  WeaponTypeDto::HOLY_GRENADE},
    {"DYNAMITE",      WeaponTypeDto::DYNAMITE},
};

WeaponTypeDto string_to_weapon_type(const std::string &type_str) {
    auto it = TYPE_MAPPING.find(type_str);
    if (it != TYPE_MAPPING.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown weapon type: " + type_str);
    }
}


ProjectileTypeDto string_to_projectile_type(const std::string &type_str) {
    const std::unordered_map<std::string, ProjectileTypeDto> PROJECTILE_TYPE_MAPPING = {
        {"P_BAZOOKA",     ProjectileTypeDto::BAZOOKA},
        {"P_MORTAR",      ProjectileTypeDto::MORTAR},
        {"GREEN_GRENADE", ProjectileTypeDto::GREEN_GRENADE},
        {"HOLY_GRENADE",  ProjectileTypeDto::HOLY_GRENADE},
        {"DYNAMITE",      ProjectileTypeDto::DYNAMITE},
        {"CLUSTLET",      ProjectileTypeDto::FRAGMENT}
    };

    auto it = PROJECTILE_TYPE_MAPPING.find(type_str);
    if (it != PROJECTILE_TYPE_MAPPING.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown projectile type: " + type_str);
    }
}

RotationType string_to_rotation_type(const std::string &rotation_type_str) {
    const std::unordered_map<std::string, RotationType> ROTATION_TYPE_MAPPING = {
        {"VELOCITY_ALIGNED",         RotationType::VELOCITY_ALIGNED},
        {"INITIAL_ANGULAR_VELOCITY", RotationType::INITIAL_ANGULAR_VELOCITY},
        {"NONE",                     RotationType::NONE}
    };

    auto it = ROTATION_TYPE_MAPPING.find(rotation_type_str);
    if (it != ROTATION_TYPE_MAPPING.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Unknown rotation type: " + rotation_type_str);
    }
}

ProjectileCfg parse_projectile_from_id(const YAML::Node &projectiles, int projectile_id) {
    const YAML::Node &projectile_node = projectiles[projectile_id];

    ProjectileCfg projectile_cfg;
    projectile_cfg.type = string_to_projectile_type(projectile_node["type"].as<std::string>());
    projectile_cfg.max_damage = projectile_node["max_damage"].as<float>();
    projectile_cfg.explosion_radius = projectile_node["explosion_radius"].as<float>();
    projectile_cfg.affected_by_wind = projectile_node["affected_by_wind"].as<bool>();
    projectile_cfg.rotation = string_to_rotation_type(projectile_node["rotation_type"].as<std::string>());
    projectile_cfg.default_explosion_countdown = projectile_node["default_explosion_countdown"].as<int>();

    if (projectile_node["fragments"]) {
        projectile_cfg.fragments.emplace();
        projectile_cfg.fragments->amount = projectile_node["fragments"]["amount"].as<int>();
        projectile_cfg.fragments->max_damage = projectile_node["fragments"]["max_damage"].as<float>();
        projectile_cfg.fragments->explosion_radius = projectile_node["fragments"]["explosion_radius"].as<float>();
        projectile_cfg.fragments->affected_by_wind = projectile_node["fragments"]["affected_by_wind"].as<bool>();
    }

    return projectile_cfg;
}

template<>
void Config<WeaponCfg>::parse_file() {
    try {
        YAML::Node weapons = YAML::LoadFile(WEAPONS_CFG_PATH);
        YAML::Node projectiles = YAML::LoadFile(PROJECTILES_CFG_PATH);
        for (const auto &entry: weapons) {
            auto id = entry.first.as<int>();
            WeaponCfg weaponCfg;
            weaponCfg.type = string_to_weapon_type(entry.second["type"].as<std::string>());

            auto projectile_id = entry.second["projectile_id"].as<int>();
            if (projectiles[projectile_id]) {
                weaponCfg.projectile = parse_projectile_from_id(projectiles, projectile_id);
            } else {
                throw std::runtime_error("Weapon needs a projectile, no melee weapons implemented for now");
            }

            weaponCfg.ammo = entry.second["ammo"].as<int>();
            weaponCfg.shoot_power = entry.second["shoot_power"].as<float>();

            // Parsing Charge (if present)
            if (entry.second["charge"]) {
                weaponCfg.charge.emplace();
                weaponCfg.charge->time_to_charge = entry.second["charge"]["time_to_charge"].as<int>();
                weaponCfg.charge->initial_charged_percentage = entry.second["charge"]["initial_charged_percentage"].as<float>();
            }
            config.emplace(id, weaponCfg);
        }
    } catch (const YAML::Exception &e) {
        std::cerr << "YAML parsing error: " << e.what() << " on WeaponConfig.cpp" << std::endl;
        throw (e);
    } catch (const std::exception &ex) {
        std::cerr << "Error in parse_file: " << ex.what() << " on WeaponConfig.cpp" << std::endl;
        throw;
    }
}

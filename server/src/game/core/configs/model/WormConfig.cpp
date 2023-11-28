#include <iostream>
#include "WormCfg.h"
#include "../Config.h"

#define WEAPONS_CFG_NAME "worms.yaml"
#define WEAPONS_CFG_PATH CONFIGS_FILE_PATH WEAPONS_CFG_NAME

template<>
void Config<WormCfg>::parse_file() {
    try {
        YAML::Node main_node = YAML::LoadFile(WEAPONS_CFG_PATH);
        WormCfg cfg;

        const YAML::Node& health_node = main_node["health"];
        cfg.health.default_health = health_node["default_health"].as<float>();
        cfg.health.disadvantage_health = health_node["disadvantage_health"].as<float>();

        const YAML::Node& body_node = main_node["body"];
        cfg.body.speed = body_node["speed"].as<float>();
        cfg.body.forward_jump_height = body_node["forward_jump_height"].as<float>();
        cfg.body.forward_jump_reach = body_node["forward_jump_reach"].as<float>();
        cfg.body.backwards_jump_height = body_node["backwards_jump_height"].as<float>();
        cfg.body.backwards_jump_reach = body_node["backwards_jump_reach"].as<float>();
        cfg.body.size = body_node["size"].as<float>();
        cfg.body.restitution = body_node["restitution"].as<float>();
        cfg.body.density = body_node["density"].as<float>();

        config.emplace(1, cfg);

    } catch (const YAML::Exception &e) {
        std::cerr << "YAML parsing error: " << e.what() << " on WeaponConfig.cpp" << std::endl;
        throw (e);
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        throw (e);
    }
}
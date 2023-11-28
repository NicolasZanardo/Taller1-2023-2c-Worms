#include <iostream>
#include "../Config.h"
#include "TurnSystemCfg.h"

#define WEAPONS_CFG_NAME "turn_system.yaml"
#define WEAPONS_CFG_PATH CONFIGS_FILE_PATH WEAPONS_CFG_NAME


template<>
void Config<TurnSystemCfg>::parse_file() {
    try {
        YAML::Node main_node = YAML::LoadFile(WEAPONS_CFG_PATH);
        TurnSystemCfg cfg;
        cfg.turn_duration = main_node["turn_duration"].as<int>();;
        cfg.match_duration = main_node["match_duration"].as<int>();;
        cfg.time_after_ending_turn = main_node["time_after_ending_turn"].as<int>();;
        config.emplace(1, cfg);

    } catch (const YAML::Exception &e) {
        std::cerr << "YAML parsing error: " << e.what() << " on WeaponConfig.cpp" << std::endl;
        throw (e);
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        throw (e);
    }
}

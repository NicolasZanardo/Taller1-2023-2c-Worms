#include "Logger.h"
#include "WeaponTypeDto.h"
#include <iostream>

void Logger::log_position(const std::string &log, float x, float y) {
    std::cout << log << " on x: " << x << " y: " << y << std::endl;
}

void Logger::log_weapon(const std::string &log, WeaponTypeDto weapon) {
    std::string name;
    switch (weapon) {
        case WeaponTypeDto::BAZOOKA:
            name = "BAZOOKA\n";
            break;
        case WeaponTypeDto::MORTAR:
            name = "MORTAR\n";
            break;
        case WeaponTypeDto::GREEN_GRENADE:
            name = "GREEN_GRENADE\n";
            break;
        case WeaponTypeDto::HOLY_GRENADE:
            name = "HOLY_GRENADE\n";
            break;
        case WeaponTypeDto::DYNAMITE:
            name = "DYNAMITE\n";
            break;
        default:
            name = "WEAPON NAME MAPPING NOT IMPLEMENTED\n";
            break;
    }
    std::cout << log << name;
}

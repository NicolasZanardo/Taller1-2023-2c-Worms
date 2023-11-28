#ifndef TP_WORMS_PROJECTILETYPEDTO_H
#define TP_WORMS_PROJECTILETYPEDTO_H

#include <cstdint>

enum class ProjectileTypeDto: uint8_t {
    NONE = 0x00,
    BAZOOKA = 0x02,
    MORTAR = 0x04,
    MORTAR_FRAGMENT = 0x05,
    GREEN_GRENADE = 0x06,
    SAINT_GRENADE = 0x08,
    RED_GRENADE = 0x010,
    RED_GRENADE_FRAGMENT = 0x011,
    BASEBALL_BAT = 0x12,
    BANANA = 0x014,
    AIRSTRIKE = 0x16,
    TELEPORTATION = 0x018
};

#endif //TP_WORMS_PROJECTILETYPEDTO_H
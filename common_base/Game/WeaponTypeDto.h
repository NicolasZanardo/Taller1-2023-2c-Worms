#ifndef TP_WORMS_WEAPONTYPEDTO_H
#define TP_WORMS_WEAPONTYPEDTO_H

#include <cstdint>

enum class WeaponTypeDto: uint8_t {
    NONE = 0x00,
    BAZOOKA = 0x01,
    MORTAR = 0x02,
    GREEN_GRENADE = 0x03,
    SAINT_GRENADE = 0x04,
    BASEBALL_BAT = 0x05,
    RED_GRENADE = 0x06,
    BANANA = 0x07,
    AIRSTRIKE = 0x08,
    TELEPORTATION = 0x09
};

#endif //TP_WORMS_WEAPONTYPEDTO_H

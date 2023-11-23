#ifndef TP_WORMS_WEAPONTYPEDTO_H
#define TP_WORMS_WEAPONTYPEDTO_H

#include <cstdint>

enum class WeaponTypeDto: uint8_t {
    BAZOOKA = 0x00,
    MORTER = 0x01,
    GREEN_GRENADE = 0x02,
    SAINT_GRENADE = 0x03,
    BASEBALL_BAT = 0x04,
    RED_GRENADE = 0x05,
    BANANA = 0x06,
    AIRSTRIKE = 0x07,
    TELEPORTATION = 0x08
};

#endif //TP_WORMS_WEAPONTYPEDTO_H

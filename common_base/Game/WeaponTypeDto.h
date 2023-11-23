#ifndef TP_WORMS_WEAPONDTO_H
#define TP_WORMS_WEAPONDTO_H

#include <cstdint>

enum class WeaponDto: uint8_t {
    BAZOOKA = 0x00,
    MORTER = 0x01,
    GREEN_GRANADE = 0x02,
    SAINT_GRANADE = 0x03,
    BASEBALL_BAT = 0x04,
    RED_GRANADE = 0x05,
    BANANA = 0x06,
    AIRSTRIKE = 0x07,
    TELEPORTATION = 0x08
};

#endif //TP_WORMS_WEAPONDTO_H

#ifndef TP_WORMS_CHEATTYPE_H
#define TP_WORMS_CHEATTYPE_H

#include <cstdint>

enum class CheatType: uint8_t {
    HEALTH = 0x00,
    MOVEMENT = 0x01,
    WEAPON = 0x02
};

#endif //TP_WORMS_CHEATTYPE_H

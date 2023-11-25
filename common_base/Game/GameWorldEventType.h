#ifndef TP_WORMS_GAMEWORLDEVENTTYPE_H
#define TP_WORMS_GAMEWORLDEVENTTYPE_H

#include <cstdint>

enum class GameWorldEventType: uint8_t {
    WORM_DEATH = 0x00,
    EXPLOSION = 0x01
};

#endif //TP_WORMS_GAMEWORLDEVENTTYPE_H

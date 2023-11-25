#ifndef TP_WORMS_GAMEWORLDVEVENTTYPE_H
#define TP_WORMS_GAMEWORLDVEVENTTYPE_H

#include <cstdint>

enum class GameWorldvEventType: uint8_t {
    WORM_DEATH = 0x00,
    EXPLOSION = 0x01
};

#endif //TP_WORMS_GAMEWORLDVEVENTTYPE_H

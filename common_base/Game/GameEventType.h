#ifndef TP_WORMS_GAMEEVENTTYPE_H
#define TP_WORMS_GAMEEVENTTYPE_H

#include <cstdint>

enum class GameEventType: uint8_t {
    WORM_DEATH = 0x00,
    EXPLOSION = 0x01
};

#endif //TP_WORMS_GAMEEVENTTYPE_H

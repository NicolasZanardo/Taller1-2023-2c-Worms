#ifndef __CLIENT_DEFS_H__
#define __CLIENT_DEFS_H__

#include <cstdint>

enum class GameEvent : uint8_t {
    RESERVED = 0x00,
    MOVE_LEFT_INIT = 0x01,
    MOVE_LEFT_END = 0x02,
    MOVE_RIGHT_INIT = 0x03,
    MOVE_RIGHT_END = 0x04,
    JUMP_FORWARD = 0x05,
    JUMP_BACKWARDS = 0x06,
    SHOOT = 0x07,
    AIM_UP_INIT = 0x08,
    AIM_DOWN_INIT = 0x09,
    AIM_UP_STOPPED = 0x010,
    AIM_DOWN_STOPPED = 0x011
};

#endif  // __CLIENT_DEFS_H__

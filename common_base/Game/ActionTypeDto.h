#ifndef COMMON_BASE_ACTION_TYPE_DTO_H
#define COMMON_BASE_ACTION_TYPE_DTO_H

#include <cstdint>

enum class ActionTypeDto : uint8_t {
    moving_left_init = 0x00,
    moving_right_init = 0x01,
    stop_moving = 0x02, // Only 1 stop moving is needed
    jump_back = 0x03,
    jump_forward = 0x04,
    shoot = 0x05,
    aim_up_init = 0x06,
    aim_down_init = 0x07,
    aim_up_stopped = 0x08,
    aim_down_stopped = 0x09

};

#endif

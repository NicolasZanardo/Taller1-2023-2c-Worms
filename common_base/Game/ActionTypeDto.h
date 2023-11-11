#ifndef COMMON_BASE_ACTIONTYPEDTO_H
#define COMMON_BASE_ACTIONTYPEDTO_H

#include <cstdint>

enum class ActionTypeDto : uint8_t {
    moving_left_init = 0x00,
    moving_right_init = 0x01,
    stop_moving = 0x02, // Only 1 stop moving is needed
    jump_back = 0x03,
    jump_forward = 0x04,
};

#endif

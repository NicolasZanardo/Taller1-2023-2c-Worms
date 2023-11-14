#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include <box2d/box2d.h>
#include "../../../../common_base/Game/wormDto.h"

class WormMovement {
    enum class MovementState : uint8_t {
        idle = 0x00,
        walking = 0x01,
        jumping = 0x02,
        shooting = 0x03,
        falling = 0x04
    };
    b2Body *body;
    MovementState state;
    const float speed = 0.5f;
    const float forwardJumpHeight = 1.0f;
    const float forwardJumpReach = 0.5f;
    const float backwardsJumpHeight = 1.2f;
    const float backwardsJumpReach = 0.2f;
    bool is_on_ground;
    bool is_moving;
    bool is_facing_right;

    int getFacingDirectionSign() const;

public:
    WormMovement(b2Body* body);

    float x() const;
    float y() const;

    WormDto::MovementState state_to_dto() const;

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    void on_update_physics();

};

#endif // SERVER_WORM_MOVEMENT_H

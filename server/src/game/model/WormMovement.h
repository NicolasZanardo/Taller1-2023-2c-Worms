#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include <box2d/box2d.h>
#include "../../../../common_base/Game/wormDto.h"

class WormMovement {
    enum class State : uint8_t {
        idle = 0x00,
        walking = 0x01,
        jumping = 0x02,
        shooting = 0x03,
        falling = 0x04
    };
    b2Body *body;

    State state;
    const float speed = 5.0f;
    const float forwardJumpHeight = 12;
    const float forwardJumpReach = 5;
    const float backwardsJumpHeight = 18;
    const float backwardsJumpReach = 2;

    bool is_on_ground;
    bool is_moving;
    bool is_facing_right;

    int getFacingDirectionSign() const;

public:

    WormMovement(b2Body* body);

    float x() const;
    float y() const;

    MovementStateDto state_to_dto() const;

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    void on_update_physics();

    bool is_still_moving();

    void stop_movement_from_input();

};

#endif // SERVER_WORM_MOVEMENT_H

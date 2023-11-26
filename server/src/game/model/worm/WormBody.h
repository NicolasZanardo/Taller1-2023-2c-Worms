#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include "box2d/box2d.h"
#include "../../../../../common_base/Game/wormDto.h"
#include "../core/Body.h"

class WormBody: public Body {
    enum class State : uint8_t {
        IDLE = 0x00,
        MOVING = 0x01,
        JUMPING = 0x02,
        FALLING = 0x03,
        SINKING = 0x04
    };

    State state;
    const float speed = 5.0f;
    const float forwardJumpHeight = 12;
    const float forwardJumpReach = 5;
    const float backwardsJumpHeight = 18;
    const float backwardsJumpReach = 2;

    const float epsilon_y = 0.1f;

    bool is_moving;
    bool is_facing_right;
    bool is_on_water;
    bool is_on_ground;
    int ground_contact_count = 0;

public:

    WormBody(b2World&  world, b2Body* body);

    bool facing_right() const;
    char facing_direction_sign() const;

    MovementStateDto state_to_dto() const;

    void on_sensed_one_new_ground_contact();
    void on_sensed_one_ground_contact_ended();

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    bool is_still_moving();

    void sink();

    void on_update();
    void on_turn_ended();

};

#endif // SERVER_WORM_MOVEMENT_H

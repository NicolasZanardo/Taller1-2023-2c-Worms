#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include "box2d/box2d.h"
#include "../../../../../common_base/Game/wormDto.h"
#include "../core/Body.h"

class WormBody: public Body {
    enum class State : uint8_t {
        idle = 0x00,
        moving = 0x01,
        going_upwards = 0x02,
        falling = 0x03
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

    int getFacingDirectionSign() const;

public:

    WormBody(b2World&  world, b2Body* body);

    bool is_on_ground;
    int ground_contact_count = 0;

    bool facing_right() const;

    MovementStateDto state_to_dto() const;

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    bool is_still_moving();

    void stop_movement_from_input();

    void on_update();
    void on_turn_ended();

};

#endif // SERVER_WORM_MOVEMENT_H

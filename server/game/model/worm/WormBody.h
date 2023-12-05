#ifndef SERVER_WORM_MOVEMENT_H
#define SERVER_WORM_MOVEMENT_H

#include "box2d/box2d.h"
#include "wormDto.h"
#include "Body.h"
#include "WormCfg.h"

class Worm;

class WormBody: public Body {
    const float speed;
    const float forward_jump_height;
    const float forward_jump_reach;
    const float backwards_jump_height;
    const float backwards_jump_reach;

    const float epsilon_y = 1.5f;

    bool is_moving;
    bool is_jumping;
    bool is_on_ground;
    int ground_contact_count = 0;
public:

    WormBody(b2World&  world, b2Body* body, WormCfg &worm_cfg);

    char facing_direction_sign() const;

    void on_sensed_one_new_ground_contact();
    void on_sensed_one_ground_contact_ended();

    void start_moving_right();

    void start_moving_left();

    void stop_moving();

    void jump_forward();

    void jump_backwards();

    void sink();

    void update(const std::shared_ptr<Worm>& worm);
    void on_turn_ended();

};

#endif // SERVER_WORM_MOVEMENT_H

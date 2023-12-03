#ifndef TP_WORMS_WORMBODYCOMPONENT_H
#define TP_WORMS_WORMBODYCOMPONENT_H

#include "box2d/box2d.h"
#include "wormDto.h"
#include "Body.h"
#include "WormCfg.h"
#include <iostream>
class Worm;

class WormBodyComponent : public Body {
protected:
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

    WormBodyComponent(
        b2World &world,
        b2Body *body,
        WormCfg &worm_cfg
    ) : Body(world, body, true),
        speed(worm_cfg.body.speed),
        forward_jump_height(
            worm_cfg.body.forward_jump_height),
        forward_jump_reach(
            worm_cfg.body.forward_jump_reach),
        backwards_jump_height(
            worm_cfg.body.backwards_jump_height),
        backwards_jump_reach(
            worm_cfg.body.backwards_jump_reach),
        is_moving(false),
        is_jumping(false),
        is_on_ground(false) {};

    explicit WormBodyComponent(std::shared_ptr<WormBodyComponent> &&other) :
        Body(other->world, other->body, other->is_facing_right),
        speed(other->speed), forward_jump_height(
        other->forward_jump_height),
        forward_jump_reach(
            other->forward_jump_reach),
        backwards_jump_height(
            other->backwards_jump_height),
        backwards_jump_reach(
            other->backwards_jump_reach),
        is_moving(other->is_jumping),
        is_jumping(other->is_jumping),
        is_on_ground(other->is_on_ground) {
        this->body = other->body;
        other->body = nullptr;
    };


    virtual char facing_direction_sign() const = 0;

    virtual void on_sensed_one_new_ground_contact() = 0;

    virtual void on_sensed_one_ground_contact_ended() = 0;

    virtual void start_moving_right() = 0;

    virtual void start_moving_left() = 0;

    virtual void stop_moving() = 0;

    virtual void jump_forward() = 0;

    virtual void jump_backwards() = 0;

    virtual void sink() = 0;

    virtual void update(const std::shared_ptr<Worm> &worm) = 0;

    virtual void on_turn_ended() = 0;

    ~WormBodyComponent() {
        std::cout << "Entered ~WormBodyComponent\n";
        Body::~Body();
    }

};

#endif //TP_WORMS_WORMBODYCOMPONENT_H

#include "WormBody.h"
#include "BuoyancyForce.h"
#include "Logger.h"

WormBody::WormBody(b2World&  world, b2Body* body, WormCfg &worm_cfg) :
        Body(world, body, true),
        state(State::IDLE),
        speed(worm_cfg.body.speed),
        forward_jump_height(worm_cfg.body.forward_jump_height),
        forward_jump_reach(worm_cfg.body.forward_jump_height),
        backwards_jump_height(worm_cfg.body.backwards_jump_height),
        backwards_jump_reach(worm_cfg.body.backwards_jump_reach),
        is_moving(false),
        is_jumping(false),
        is_on_water(false),
        is_on_ground(false){};

bool WormBody::facing_right() const {
    return is_facing_right;
}

void WormBody::on_sensed_one_new_ground_contact() {
    ground_contact_count++;
    is_on_ground = (ground_contact_count > 0);
    is_jumping = false;
}

void WormBody::on_sensed_one_ground_contact_ended() {
    ground_contact_count--;
    is_on_ground = (ground_contact_count > 0);
}


char WormBody::facing_direction_sign() const {
    if (is_facing_right) {
        return 1;
    } else {
        return -1;
    }
}

void WormBody::start_moving_right() {
    if (is_on_ground) {
        is_facing_right = true;
        is_moving = true;
    }
}

void WormBody::start_moving_left() {
    if (is_on_ground) {
        is_facing_right = false;
        is_moving = true;
    }
}

void WormBody::stop_moving() { //left right
    if (is_on_ground) {
        is_moving = false;
        b2Vec2 velocity = body->GetLinearVelocity();
        velocity.x = 0.0f;
        body->SetLinearVelocity(velocity);
    }
}

void WormBody::jump_forward() {
    if (is_on_ground) {
        is_moving = false;
        is_jumping = true;
        body->SetLinearVelocity(b2Vec2(0,0));
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                    facing_direction_sign() * forward_jump_reach * body->GetMass(),
                    forward_jump_height * body->GetMass()
                        ), true);
    }
}

void WormBody::jump_backwards() {
    if (is_on_ground) {
        is_moving = false;
        is_jumping = true;
        body->SetLinearVelocity(b2Vec2(0,0));
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                    (-facing_direction_sign()) * backwards_jump_reach * body->GetMass(),
                    backwards_jump_height * body->GetMass()
                        ),
                true);
    }
}

void WormBody::sink() {
    is_moving = false;
    is_on_ground = false;
    is_on_water = true;
}

void WormBody::on_update() {
    float y_velocity = body->GetLinearVelocity().y;

    if (is_moving && is_on_ground) {
        body->SetLinearVelocity((b2Vec2(facing_direction_sign() * speed, y_velocity)));
    } else if(is_on_water) {
        BuoyancyForce force(world);
        force.apply(this->body);
    }

    if (is_on_water) {
        state = State::SINKING;
    } else if (is_jumping) {
        state = State::JUMPING;
    } else if (y_velocity < -epsilon_y) {
        state = State::FALLING;
    } else {
        if (abs(body->GetLinearVelocity().x) < epsilon_y) {
            state = State::IDLE;
        } else {
            state = State::MOVING;
        }
    }
}

void WormBody::on_turn_ended() {
    is_moving = false;
}

bool WormBody::is_still_moving() {
    return body->GetLinearVelocity().x != 0 && body->GetLinearVelocity().y != 0;
}


MovementStateDto WormBody::state_to_dto() const {
    switch (state) {
        case State::IDLE:
            return MovementStateDto::IDLE;
        case State::MOVING:
            return MovementStateDto::MOVING;
        case State::JUMPING:
            return MovementStateDto::GOING_UPWARDS;
        case State::FALLING:
            return MovementStateDto::FALLING;
        case State::SINKING:
            return MovementStateDto::SINKING;
    }
}

#include "WormBody.h"
#include <iostream>

WormBody::WormBody(b2World&  world, b2Body* body) :
        Body(world, body),
        state(State::idle),
        is_moving(false),
        is_facing_right(true),
        is_on_ground(false) {};

bool WormBody::facing_right() const {
    return is_facing_right;
}

int WormBody::getFacingDirectionSign() const {
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
        body->SetLinearVelocity(b2Vec2(0,0));
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                        getFacingDirectionSign() * forwardJumpReach * body->GetMass(),
                        forwardJumpHeight* body->GetMass()
                        ), true);
    }
}

void WormBody::jump_backwards() {
    if (is_on_ground) {
        is_moving = false;
        body->SetLinearVelocity(b2Vec2(0,0));
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                        (-getFacingDirectionSign())  * backwardsJumpReach * body->GetMass(),
                        backwardsJumpHeight * body->GetMass()
                        ),
                true);
    }
}

void WormBody::on_update() {
    float y_velocity = body->GetLinearVelocity().y;

    if (is_moving && is_on_ground) {
        body->SetLinearVelocity((b2Vec2(getFacingDirectionSign() * speed, body->GetLinearVelocity().y)));
    }

    if (y_velocity > epsilon_y) {
        state = State::going_upwards;
    } else if (y_velocity < -epsilon_y) {
        state = State::falling;
    } else {
        if (body->GetLinearVelocity().x == 0.0f) {
            state = State::idle;
        } else {
            state = State::moving;
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
        case State::idle:
            return MovementStateDto::idle;
        case State::moving:
            return MovementStateDto::moving;
        case State::going_upwards:
            return MovementStateDto::going_upwards;
        case State::falling:
            return MovementStateDto::falling;
    }
}
#include "WormMovement.h"
#include <iostream>

WormMovement::WormMovement(b2Body *body) :
        body(body),
        state(State::idle),
        is_moving(false),
        is_facing_right(true),
        is_on_ground(false) {};

float WormMovement::x() const {
    return body->GetPosition().x;
}

float WormMovement::y() const {
    return body->GetPosition().y;
}

bool WormMovement::facing_right() const {
    return is_facing_right;
}

int WormMovement::getFacingDirectionSign() const {
    if (is_facing_right) {
        return 1;
    } else {
        return -1;
    }
}

void WormMovement::start_moving_right() {
    std::cout << "Calling start_moving_right\n";
    if (is_on_ground) {
        is_facing_right = true;
        is_moving = true;
    }
}

void WormMovement::start_moving_left() {
    if (is_on_ground) {
        is_facing_right = false;
        is_moving = true;
    }
}

void WormMovement::stop_moving() { //left right
    if (is_on_ground) {
        is_moving = false;
        b2Vec2 velocity = body->GetLinearVelocity();
        velocity.x = 0.0f;
        body->SetLinearVelocity(velocity);
    }
}

void WormMovement::jump_forward() {
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

void WormMovement::jump_backwards() {
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

void WormMovement::on_update_physics() {
    if (is_on_ground) {
        std::cout << "On ground\n";
    } else {
        std::cout << "On air\n";
    }

    // y
    float y_velocity = body->GetLinearVelocity().y;

    // x
    if (is_moving && is_on_ground) {
        body->SetLinearVelocity((b2Vec2(getFacingDirectionSign() * speed, body->GetLinearVelocity().y)));
    }

    // Update state according to the actual physics
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

bool WormMovement::is_still_moving() {
    return body->GetLinearVelocity().x != 0 && body->GetLinearVelocity().y != 0;
}

void WormMovement::stop_movement_from_input() {
    is_moving = false;
}

MovementStateDto WormMovement::state_to_dto() const {
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
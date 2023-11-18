#include "WormMovement.h"

WormMovement::WormMovement(b2Body *body) :
        body(body),
        state(State::idle),
        is_on_ground(false),
        is_moving(false),
        is_facing_right(true) {};

float WormMovement::x() const {
    return body->GetPosition().x;
}

float WormMovement::y() const {
    return body->GetPosition().y;
}

int WormMovement::getFacingDirectionSign() const {
    if (is_facing_right) {
        return 1;
    } else {
        return -1;
    }
}

void WormMovement::start_moving_right() {
    if (state != State::jumping) {
        is_facing_right = true;
        is_moving = true;
        state = State::walking;
    }
}

void WormMovement::start_moving_left() {
    if (state != State::jumping) {
        is_facing_right = false;
        is_moving = true;
        state = State::walking;
    }
}

void WormMovement::stop_moving() {
    is_moving = false;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void WormMovement::jump_forward() {
    if (is_on_ground) {
        is_moving = false;
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                        getFacingDirectionSign() * forwardJumpReach * body->GetMass(),
                        forwardJumpHeight* body->GetMass()
                        ), true);
        is_on_ground = false;
        state = State::jumping;
    }
}

void WormMovement::jump_backwards() {
    if (is_on_ground) {
        is_moving = false;
        body->ApplyLinearImpulseToCenter(
                b2Vec2(
                        (-getFacingDirectionSign())  * backwardsJumpReach * body->GetMass(),
                        backwardsJumpHeight * body->GetMass()
                        ),
                true);
        is_on_ground = false;
        state = State::jumping;
    }
}

void WormMovement::on_update_physics() {
    // y
    float y_velocity = body->GetLinearVelocity().y;
    if (y_velocity == 0.0f) {
        is_on_ground = true;
        if (body->GetLinearVelocity().x == 0.0f) {
            state = State::idle;
        }

    } else if (y_velocity < 0.0f) {
        state = State::falling;
    }

    // x
    if (is_moving) {
        body->SetLinearVelocity((b2Vec2(getFacingDirectionSign() * speed, body->GetLinearVelocity().y)));
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
        case State::walking:
            return MovementStateDto::walking;
        case State::jumping:
            return MovementStateDto::jumping;
        case State::shooting:
            return MovementStateDto::shooting;
        case State::falling:
            return MovementStateDto::falling;
    }
}
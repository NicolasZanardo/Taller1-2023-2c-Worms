#include "WormMovement.h"

WormMovement::WormMovement(b2Body *body) :
        body(body),
        state(MovementState::idle),
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
    if (state != MovementState::jumping) {
        is_facing_right = true;
        is_moving = true;
        state = MovementState::walking;
    }
}

void WormMovement::start_moving_left() {
    if (state != MovementState::jumping) {
        is_facing_right = false;
        is_moving = true;
        state = MovementState::walking;
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
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * forwardJumpReach, forwardJumpHeight), true);
        is_on_ground = false;
        state = MovementState::jumping;
    }
}

void WormMovement::jump_backwards() {
    if (is_on_ground) {
        is_moving = false;
        body->ApplyLinearImpulseToCenter(b2Vec2((-getFacingDirectionSign()) * backwardsJumpReach, backwardsJumpHeight),
                                         true);
        is_on_ground = false;
        state = MovementState::jumping;
    }
}

void WormMovement::on_update_physics() {
    // y
    float y_velocity = body->GetLinearVelocity().y;
    if (y_velocity == 0.0f) {
        is_on_ground = true;
        if (body->GetLinearVelocity().x == 0.0f) {
            state = MovementState::idle;
        }

    } else if (y_velocity < 0.0f) {
        state = MovementState::falling;
    }

    // x
    if (is_moving) {
        body->ApplyLinearImpulseToCenter((b2Vec2(getFacingDirectionSign() * speed, 0.0f)), true);
    }
}

WormDto::MovementState WormMovement::state_to_dto() const {
    switch (state) {
        case MovementState::idle:
            return WormDto::MovementState::idle;
        case MovementState::walking:
            return WormDto::MovementState::walking;
        case MovementState::jumping:
            return WormDto::MovementState::jumping;
        case MovementState::shooting:
            return WormDto::MovementState::shooting;
        case MovementState::falling:
            return WormDto::MovementState::falling;
    }
}
#include "Worm.h"
#include <iostream>

Worm::Worm(size_t id) :
        Instance(id),
        state(State::idle),
        is_moving(false),
        is_facing_right(true) {}

WormDto Worm::toWormDto(size_t clientId) {
    b2Vec2 position = body->GetPosition();
    return WormDto(
            clientId,
            id,
            position.x,
            position.y,
            health,
            stateToDto()
    );
}

// TODO separate Movement logic
// Movement

int Worm::getFacingDirectionSign() const {
    if (is_facing_right) {
        return 1;
    } else {
        return -1;
    }
}

void Worm::startMovingRight() {
    std::cout << "startMovingRight was called" << std::endl;
    if (state != State::jumping) {
        is_facing_right = true;
        std::cout << "When start to move to right, facing sign is: " << getFacingDirectionSign() << std::endl;
        is_moving = true;
        state = State::walking;
    }
}

void Worm::startMovingLeft() {
    std::cout << "startMovingLeft was called" << std::endl;
    if (state != State::jumping) {
        is_facing_right = false;
        is_moving = true;
        state = State::walking;
    }
}

void Worm::stopMoving() {
    is_moving = false;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void Worm::jumpForward() {
    if (is_on_ground) {
        is_moving = false;
        state = State::jumping;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * forwardJumpReach, forwardJumpHeight), true);
        is_on_ground = false;
    }
}

void Worm::jumpBackwards() {
    if (is_on_ground) {
        is_moving = false;
        state = State::jumping;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * backwardsJumpReach, backwardsJumpHeight),
                                         true);
        is_on_ground = false;
    }
}

WormDto::State Worm::stateToDto() const {
    switch (state) {
        case State::idle:
            return WormDto::State::idle;
        case State::walking:
            return WormDto::State::walking;
        case State::jumping:
            return WormDto::State::jumping;
        case State::shooting:
            return WormDto::State::shooting;
        case State::falling:
            return WormDto::State::falling;
        case State::damaged:
            return WormDto::State::damaged;
        case State::dead:
            return WormDto::State::dead;
    }
}


void Worm::onUpdatePhysics() {
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
        std::cout << "Facing direction sign is: " << getFacingDirectionSign() << std::endl;
        body->ApplyLinearImpulseToCenter((b2Vec2(getFacingDirectionSign() * speed, 0.0f)), true);
    }
}

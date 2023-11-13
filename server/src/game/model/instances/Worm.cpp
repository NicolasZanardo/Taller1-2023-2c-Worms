#include "Worm.h"

Worm::Worm(size_t id) : Instance(id) {}

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

short Worm::getFacingDirectionSign() const {
    if (isFacingRight) {
        return 1;
    } else {
        return -1;
    }
}

void Worm::startMovingRight() {
    isFacingRight = true;
    state = State::walking;
    body->SetLinearVelocity((b2Vec2(speed, 0.0f)));
}

void Worm::startMovingLeft() {
    isFacingRight = false;
    state = State::walking;
    body->SetLinearVelocity((b2Vec2(-speed, 0.0f)));
}

void Worm::stopMoving() {
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
    state = State::idle;
}

void Worm::jumpForward() {
    if (is_on_ground) {
        state = State::jumping;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * forwardJumpReach, forwardJumpHeight), true);
        is_on_ground = false;
    }
}

void Worm::jumpBackwards() {
    if (is_on_ground) {
        state = State::jumping;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * backwardsJumpReach, backwardsJumpHeight), true);
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
    float y_velocity = body->GetLinearVelocity().y;
    if (y_velocity == 0.0f) {
        is_on_ground = true;
    } else if (y_velocity < 0.0f) {
        state = State::falling;
    }
}

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
            WormDto::State::idle// Todo Hardcoded Server states do not necessarily map 1 to 1 to the dto states needed by client
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
    body->SetLinearVelocity((b2Vec2(speed, 0.0f)));
}

void Worm::startMovingLeft() {
    isFacingRight = false;
    body->SetLinearVelocity((b2Vec2(-speed, 0.0f)));
}

void Worm::stopMoving() {
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void Worm::jumpForward() {
    if (!isJumping) {
        isJumping = true;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * forwardJumpReach, forwardJumpHeight), true);
    }
}

void Worm::jumpBackwards() {
    if (!isJumping) {
        isJumping = true;
        body->ApplyLinearImpulseToCenter(b2Vec2(getFacingDirectionSign() * backwardsJumpReach, backwardsJumpHeight), true);

    }
}

// TODO This? or detect jump false with collision?
void Worm::onUpdatePhysics() {
    // Update method to be called in the main game loop
    // Reset the jump state when the worm is on the ground
    if (body->GetLinearVelocity().y == 0.0f) {
        isJumping = false;
    }
}

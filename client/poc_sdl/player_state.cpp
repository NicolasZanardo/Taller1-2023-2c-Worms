#include "player_state.h"

PlayerState::PlayerState(Sprite& sprite)
    : an(sprite, true)
    , facingLeft(false)
    , moving(false)
    , x(300), y(300) {}

void PlayerState::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void PlayerState::render() {
    an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
}

void PlayerState::moveRigth() {
    moving = true;
    facingLeft = false;
}

void PlayerState::moveLeft() {
    moving = true;
    facingLeft = true;
}

void PlayerState::stopMoving() {
    moving = false;
}

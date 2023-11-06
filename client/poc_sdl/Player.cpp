#include "Player.h"

Player::Player(Sprite& sprite)
    : an(sprite, true)
    , facingLeft(false)
    , moving(false)
    , x(300), y(300) {}

void Player::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Player::render() {
    an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
}

void Player::moveRigth() {
    moving = true;
    facingLeft = false;
}

void Player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Player::stopMoving() {
    moving = false;
}

#include "Player.h"

Player::Player(Sprite& sprite)
    : an(sprite)
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
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(SDL2pp::Rect(x, y, 200, 200), flip);
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

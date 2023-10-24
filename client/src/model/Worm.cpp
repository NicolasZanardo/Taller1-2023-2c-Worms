#include "Worm.h"
Worm::Worm(SDL2pp::Texture &texture): an(texture), facingLeft(false), moving(false), x(300), y(300) {}

Worm::~Worm() {}

void Worm::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void Worm::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, 200, 200), flip);
}

void Worm::moveRight() {
    moving = true;
    facingLeft = false;
}

void Worm::moveLeft() {
    moving = true;
    facingLeft = true;
}

void Worm::stopMoving() {
    moving = false;
}
#include "animation.h"

Animation::Animation(Sprite& sprite, bool img_looking_left)
    : img_looking_left(img_looking_left)
    , elapsed(0.0f)
    , frame_selector(sprite.getHeight() / sprite.getWidth(), 0)
    , sprite(&sprite) {}

void Animation::update(float dt) {
    this->elapsed += dt;
    while (this->elapsed > FRAME_RATE) {
        this->frame_selector.advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}
void Animation::render(const SDL2pp::Rect dest, bool facing_left) {
    SDL_RendererFlip flip = (this->img_looking_left != facing_left) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    this->sprite->render(this->frame_selector.getCurrentFrame(), dest, flip);
}

#include "Animation.h"

Animation::Animation(Sprite& sprite)
    : elapsed(0.0f)
    , frame_selector(sprite.getWidth() / sprite.getHeight(), 0)
    , sprite(&sprite) {}

void Animation::update(float dt) {
    this->elapsed += dt;
    while (this->elapsed > FRAME_RATE) {
        this->frame_selector.advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

void Animation::render(const SDL2pp::Rect dest, SDL_RendererFlip &flipType) {
    this->sprite->render(this->frame_selector.getCurrentFrame(), dest, flipType);
}

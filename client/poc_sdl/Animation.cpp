/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */
#include <SDL2pp/SDL2pp.hh>

#include <cassert>
#include "Animation.h"

Animation::Animation(SDL2pp::Texture &texture)
    : texture(texture)
    , size(this->texture.GetHeight()), elapsed(0.0f)
    , frame_selector(this->texture.GetWidth() / this->texture.GetHeight(), 0) {
}

Animation::~Animation() {}

void Animation::update(float dt) {
    this->elapsed += dt;
    while (this->elapsed > FRAME_RATE) {
        this->frame_selector.advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

void Animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {
    uint16_t frame_to_draw = this->frame_selector.getCurrentFrame();

    renderer.Copy(
            texture,
            SDL2pp::Rect(1 + (1 + this->size) * frame_to_draw, 0, this->size, this->size),
            dst,
            0.0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
        );
}

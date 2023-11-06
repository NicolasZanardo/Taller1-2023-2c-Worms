#include "./sprite.h"

Sprite::Sprite(SDL2pp::Renderer& renderer_ref)
    : renderer_ptr(&renderer_ref)
    , texture(*renderer_ptr, SDL2pp::Surface("assets/soldier2.png").SetColorKey(true, 0))
    , size(texture.GetHeight()) {}

void Sprite::render(uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {
    this->renderer_ptr->Copy(
        this->texture,
        SDL2pp::Rect(1 + (1 + this->size) * num_frame, 0, this->size, this->size),
        dst,
        0.0,
        SDL2pp::NullOpt,
        flipType
    );
}
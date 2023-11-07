#include "./sprite.h"

Sprite::Sprite(SDL2pp::Renderer& renderer_ref)
    : renderer_ptr(&renderer_ref)
    , texture(*renderer_ptr, SDL2pp::Surface("assets/wwalk.png"))
    , size(texture.GetWidth()) {}

void Sprite::render(uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    this->renderer_ptr->Copy(
        this->texture,
        SDL2pp::Rect(0, this->size * num_frame, this->size, this->size),
        dst,
        0.0,
        SDL2pp::NullOpt,
        flip_type
    );
}

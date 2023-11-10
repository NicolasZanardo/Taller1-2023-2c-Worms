#include "./sprite.h"

Sprite::Sprite(SDL2pp::Renderer& renderer_ref, const std::string& sprite_file)
    : renderer_ptr(&renderer_ref)
    , texture(*renderer_ptr, SDL2pp::Surface(sprite_file.c_str()))
    , size(texture.GetWidth()) {}

Sprite::Sprite(Sprite&& other)
    : renderer_ptr(other.renderer_ptr)
    , texture(std::move(other.texture))
    , size(other.size) {}

Sprite& Sprite::operator=(Sprite&& other) {
    if (&other == this) {
		return *this;
    }

	this->renderer_ptr = other.renderer_ptr;
    this->texture = std::move(other.texture);
    this->size = other.size;

	return *this;
}

void Sprite::setColorMod(uint8_t r, uint8_t g, uint8_t b) {
    this->texture.SetColorMod(r, g, b);
}

void Sprite::render(const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    this->renderer_ptr->Copy(
        this->texture,
        SDL2pp::NullOpt,
        dst,
        0.0,
        SDL2pp::NullOpt,
        flip_type
    );
}

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

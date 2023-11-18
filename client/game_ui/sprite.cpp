#include "./sprite.h"

Sprite::Sprite(SDL2pp::Renderer& renderer_ref, const std::string& sprite_file,
                                uint16_t frame_width, uint16_t frame_height, uint16_t sep)
    : renderer_ptr(&renderer_ref)
    , texture(*renderer_ptr, SDL2pp::Surface(sprite_file.c_str()))
    , frame_width(frame_width), frame_height(frame_height)
    , sep(sep) {}

Sprite::Sprite(SDL2pp::Renderer& renderer_ref, const std::string& sprite_file,
               uint16_t frame_width, uint16_t frame_height, uint16_t sep, bool flag, Uint32 key)
        : renderer_ptr(&renderer_ref)
        , texture(*renderer_ptr, SDL2pp::Surface(sprite_file.c_str()).SetColorKey(flag, key))
        , frame_width(frame_width), frame_height(frame_height)
        , sep(sep) {}

Sprite::Sprite(Sprite&& other)
    : renderer_ptr(other.renderer_ptr)
    , texture(std::move(other.texture))
    , frame_width(other.frame_width)
    , frame_height(other.frame_height)
    , sep(other.sep) {}

Sprite& Sprite::operator=(Sprite&& other) {
    if (&other == this) {
		return *this;
    }

	this->renderer_ptr = other.renderer_ptr;
    this->texture = std::move(other.texture);
    this->frame_width = other.frame_width;
    this->frame_height = other.frame_height;
    this->sep = other.sep;

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

void Sprite::render(const SDL2pp::Rect dst, double angle, SDL_RendererFlip &flip_type) {
    this->renderer_ptr->Copy(
        this->texture,
        SDL2pp::NullOpt,
        dst,
        angle,
        SDL2pp::NullOpt,
        flip_type
    );
}

void Sprite::render(uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    this->renderer_ptr->Copy(
        this->texture,
        SDL2pp::Rect(0, (this->frame_height + this->sep) * num_frame, this->frame_width, this->frame_height),
        dst,
        0.0,
        SDL2pp::NullOpt,
        flip_type
    );
}

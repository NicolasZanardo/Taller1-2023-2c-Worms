#ifndef  __SPRITE_H__
#define __SPRITE_H__

#include <cstdint>

#include <SDL2pp/SDL2pp.hh>

class Sprite {
public:
    Sprite() = delete;
    explicit Sprite(SDL2pp::Renderer& renderer_ref);
    ~Sprite() = default;

    void render(uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type);
    uint32_t getWidth() const { return this->texture.GetWidth(); }
    uint32_t getHeight() const { return this->texture.GetHeight(); }

private:
    SDL2pp::Renderer* renderer_ptr;
    SDL2pp::Texture texture;
    uint16_t size;
};

#endif  // __SPRITE_H__

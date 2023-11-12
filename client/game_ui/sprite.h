#ifndef  __SPRITE_H__
#define __SPRITE_H__

#include <cstdint>

#include <SDL2pp/SDL2pp.hh>

class Sprite {
public:
    Sprite() = delete;
    explicit Sprite(SDL2pp::Renderer& renderer_ref, const std::string& sprite_file,
                                    uint16_t frame_width, uint16_t frame_height, uint16_t sep);
    ~Sprite() = default;

    Sprite(Sprite&& other);
    Sprite& operator=( Sprite&& other);

    Sprite(const Sprite& other) = delete;
    Sprite& operator=(const Sprite& other) = delete;

    void setColorMod(uint8_t r, uint8_t g, uint8_t b);
    void render(const SDL2pp::Rect dst, SDL_RendererFlip &flip_type);
    void render(const SDL2pp::Rect dst, double angle, SDL_RendererFlip &flip_type);
    void render(uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type);
    uint32_t getWidth() const { return this->texture.GetWidth(); }
    uint32_t getHeight() const { return this->texture.GetHeight(); }

private:
    SDL2pp::Renderer* renderer_ptr;
    SDL2pp::Texture texture;
    uint16_t frame_width;
    uint16_t frame_height;
    uint16_t sep;
};

#endif  // __SPRITE_H__
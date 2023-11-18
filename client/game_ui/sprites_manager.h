#ifndef __SPRITES_MANAGER_H__
#define __SPRITES_MANAGER_H__

#include <map>
#include <string>

#include <SDL2pp/SDL2pp.hh>

#include "sprite.h"

class SpritesManager {
public:
    SpritesManager() = delete;
    explicit SpritesManager(SDL2pp::Renderer& renderer);
    ~SpritesManager() = default;

    void addSprite(std::string id, std::string sprite_file, uint16_t frame_width, uint16_t frame_height, uint16_t sep);
    void addSprite(std::string id, std::string sprite_file, uint16_t frame_width, uint16_t frame_height, uint16_t sep, bool flag, Uint32 key);
    void renderSprite(std::string id, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type);
    void renderSprite(std::string id, const SDL2pp::Rect dst, double angle, SDL_RendererFlip &flip_type);
    void renderSprite(std::string id, uint16_t num_frame, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type);

private:
    Sprite& check_exists(const std::string& id);

    SDL2pp::Renderer* renderer;
    std::map<std::string, Sprite> sprites;
};

#endif  // __SPRITES_MANAGER_H__

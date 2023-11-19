#ifndef _CLIENT_GAME_SPRITE_INFO_H_
#define _CLIENT_GAME_SPRITE_INFO_H_

#include <string>
#include <cstdint>
#include <SDL2pp/SDL2pp.hh>

class GameSpriteInfo {
    uint16_t frame_width;
    uint16_t frame_height;
    uint16_t frame_sep;

    public:
    float frame_speed;
    SDL2pp::Texture texture;
    uint16_t frame_count;
    GameSpriteInfo(SDL2pp::Renderer& renderer, std::string texture_file_path);
    GameSpriteInfo(SDL2pp::Renderer& renderer, std::string texture_file_path, 
        uint16_t frame_width, uint16_t frame_height, 
        uint16_t frame_sep, float frame_speed
    );

    SDL2pp::Rect image_frame(const uint16_t frame) const;
};
#endif

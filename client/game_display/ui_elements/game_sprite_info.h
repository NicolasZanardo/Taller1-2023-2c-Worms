#ifndef _CLIENT_GAME_SPRITE_INFO_H_
#define _CLIENT_GAME_SPRITE_INFO_H_

#include <string>
#include <cstdint>
#include <SDL2pp/SDL2pp.hh>


enum SpriteAnimationType {
    LOOP, REVERSE, FREEZE, NONE, BY_ANGLE
};

class GameSpriteInfo {
    uint16_t frame_width;
    uint16_t frame_height;
    uint16_t frame_xoffset;
    uint16_t frame_yoffset;
    uint16_t frame_sep;

public:
    SpriteAnimationType animation;
    float frame_speed;
    SDL2pp::Texture texture;
    uint16_t frame_count;

    GameSpriteInfo(SDL2pp::Renderer &renderer, std::string texture_file_path);

    GameSpriteInfo(SDL2pp::Renderer &renderer, std::string texture_file_path,
                   uint16_t frame_width, uint16_t frame_height,
                   uint16_t frame_xoffset, uint16_t frame_yoffset,
                   uint16_t frame_sep, SpriteAnimationType animation, float frame_speed
    );

    GameSpriteInfo(SDL2pp::Renderer &renderer, std::string texture_file_path,
                   uint16_t frame_width, uint16_t frame_height,
                   uint16_t frame_xoffset, uint16_t frame_yoffset,
                   uint16_t frame_sep, SpriteAnimationType animation, float frame_speed, bool flag,
                   Uint32 key
    );

    SDL2pp::Rect image_frame(const uint16_t frame) const;
};

#endif

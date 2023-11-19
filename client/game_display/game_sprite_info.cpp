#include "game_sprite_info.h"

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer, 
        std::string texture_file_path
    ) : 
    frame_width(0),
    frame_height(0),
    frame_sep(0),
    frame_speed(0),
    texture(renderer, SDL2pp::Surface(texture_file_path.c_str())), 
    frame_count(0)
    { }

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer, 
        std::string texture_file_path, 
        uint16_t frame_width, 
        uint16_t frame_height, 
        uint16_t frame_sep,
        float frame_speed
    ) : 
    frame_width(frame_width),
    frame_height(frame_height),
    frame_sep(frame_sep),
    frame_speed(frame_speed),
    texture(renderer,SDL2pp::Surface(texture_file_path.c_str())),
    frame_count(texture.GetHeight() / (frame_height + frame_sep))
    { }

SDL2pp::Rect GameSpriteInfo::image_frame(const uint16_t frame) const {
    return SDL2pp::Rect(0,(frame_height + frame_sep)*(frame % frame_count), frame_width, frame_height);
}

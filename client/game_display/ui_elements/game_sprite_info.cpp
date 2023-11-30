#include "game_sprite_info.h"
#include "sprite_animation.h"

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer, 
        std::string texture_file_path
    ) : 
    frame_width(0),
    frame_height(0),
    frame_sep(0),
    angle_ini(0),
    angle_span(0),
    animation(SpriteAnimationType::NONE),
    frame_speed(0),
    texture(renderer, SDL2pp::Surface(texture_file_path.c_str())),
    frame_count(0)
    { }

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer,
        std::string texture_file_path,
        uint16_t frame_width,
        uint16_t frame_height,
        uint16_t frame_xoffset,
        uint16_t frame_yoffset,
        uint16_t frame_sep,
        SpriteAnimationType animation,
        float frame_speed
) :
        frame_width(frame_width),
        frame_height(frame_height),
        frame_xoffset(frame_xoffset),
        frame_yoffset(frame_yoffset),
        frame_sep(frame_sep),
        angle_ini(0),
        angle_span(0),
        animation(animation),
        frame_speed(frame_speed),
        texture(renderer,SDL2pp::Surface(texture_file_path.c_str())),
        frame_count(texture.GetHeight() / (frame_height + frame_sep))
{ }

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer, 
        std::string texture_file_path, 
        uint16_t frame_width, 
        uint16_t frame_height,
        uint16_t frame_xoffset,
        uint16_t frame_yoffset,
        uint16_t frame_sep,
        SpriteAnimationType animation,
        float frame_speed,
        bool flag,
        Uint32 key
    ) : 
    frame_width(frame_width),
    frame_height(frame_height),
    frame_xoffset(frame_xoffset),
    frame_yoffset(frame_yoffset),
    frame_sep(frame_sep),
    angle_ini(0),
    angle_span(0),
    animation(animation),
    frame_speed(frame_speed),
    texture(renderer,SDL2pp::Surface(texture_file_path.c_str()).SetColorKey(flag, key)),
    frame_count(texture.GetHeight() / (frame_height + frame_sep))
    { }

GameSpriteInfo::GameSpriteInfo(
        SDL2pp::Renderer& renderer, 
        std::string texture_file_path, 
        uint16_t frame_width, 
        uint16_t frame_height,
        uint16_t frame_xoffset,
        uint16_t frame_yoffset,
        uint16_t frame_sep,
        float angle_ini,
        float angle_span
    ) : 
    frame_width(frame_width),
    frame_height(frame_height),
    frame_xoffset(frame_xoffset),
    frame_yoffset(frame_yoffset),
    frame_sep(frame_sep),
    angle_ini(angle_ini),
    angle_span(angle_span),
    animation(SpriteAnimationType::BY_ANGLE),
    frame_speed(0),
    texture(renderer,SDL2pp::Surface(texture_file_path.c_str())),
    frame_count(texture.GetHeight() / (frame_height + frame_sep))
    { }

SDL2pp::Rect GameSpriteInfo::image_frame(const uint16_t frame) const {
    return SDL2pp::Rect(frame_xoffset, frame_yoffset + (frame_height + frame_sep)*(frame % frame_count), frame_width, frame_height);
}

SpriteAnimation* GameSpriteInfo::new_animation() {
    switch(animation) {
        case SpriteAnimationType::BY_ANGLE:
            return new RotationAnimation(*this, angle_ini, angle_span);
        case SpriteAnimationType::LOOP:
            return new LoopingAnimation(*this);
        case SpriteAnimationType::REVERSE:
            return new ReversingAnimation(*this);
        case SpriteAnimationType::NONE:
            return new NoAnimation(*this);
        case SpriteAnimationType::FREEZE:
            return new FreezingAnimation(*this);
    }
    return new NoAnimation(*this);
}
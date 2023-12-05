#ifndef _CLIENT_GAME_SPRITE_MANAGER_H_
#define _CLIENT_GAME_SPRITE_MANAGER_H_

#include <map>
#include <string>
#include <cstdint>
#include "ui_elements/game_sprite_info.h"

enum TextType { title, gametext };
class ResourceManager {
    SDL2pp::Renderer& renderer;
    std::map<std::string, GameSpriteInfo*> textures;
    std::map<TextType, SDL2pp::Font*> fonts;
    public:
    explicit ResourceManager(SDL2pp::Renderer& renderer);
    ~ResourceManager();
    
    void add_texture(const std::string keyname, const std::string file_path);
    void add_texture(
        const std::string keyname, const std::string file_path, 
        uint16_t image_width, uint16_t image_height, 
        uint16_t image_xoffset, uint16_t image_yoffset, 
        uint16_t image_sep, SpriteAnimationType animation, float image_speed
    );

    void add_texture(
            const std::string keyname, const std::string file_path,
            uint16_t image_width, uint16_t image_height,
            uint16_t image_xoffset, uint16_t image_yoffset,
            uint16_t image_sep, SpriteAnimationType animation, float image_speed, bool flag, Uint32 key
    );

    void add_texture(
            const std::string keyname, const std::string file_path,
            uint16_t image_width, uint16_t image_height,
            uint16_t image_xoffset, uint16_t image_yoffset,
            uint16_t image_sep, float angle_ini, float angle_span
    );

    
    GameSpriteInfo* get_sprite(const std::string idx);
    SDL2pp::Font* get_font(TextType type);
};
#endif
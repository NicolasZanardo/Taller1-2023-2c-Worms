#ifndef _CLIENT_GAME_SPRITE_MANAGER_H_
#define _CLIENT_GAME_SPRITE_MANAGER_H_

#include <map>
#include <string>
#include <cstdint>
#include <SDL2pp/SDL2pp.hh>
#include "game_sprite_info.h"

class GameSpriteManager {
    SDL2pp::Renderer& renderer;
    std::map<std::string, GameSpriteInfo*> textures;

    public:
    explicit GameSpriteManager(SDL2pp::Renderer& renderer);
    ~GameSpriteManager();
    
    void add_texture(const std::string keyname, const std::string file_path);
    void add_texture(
        const std::string keyname, const std::string file_path, 
        uint16_t image_width, uint16_t image_height, uint16_t image_sep
    );
    
    GameSpriteInfo* get(const std::string idx);
};
#endif
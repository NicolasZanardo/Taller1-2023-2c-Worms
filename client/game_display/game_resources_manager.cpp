#include "game_resources_manager.h"
using namespace std;

ResourceManager::ResourceManager(SDL2pp::Renderer &renderer) :
    renderer(renderer), fonts({
{ TextType::title, new SDL2pp::Font("resources/misc/Vera.ttf", 30) },
{ TextType::gametext, new SDL2pp::Font("resources/misc/Vera.ttf", 12) }
    })
    { }

ResourceManager::~ResourceManager() {
    for (auto [key, val]: textures) {
        delete (val);
    }
    for (auto [key, val]: fonts) {
        delete (val);
    }
}

void ResourceManager::add_texture(const string keyname, const string file_path) {
    textures.emplace(keyname, new GameSpriteInfo(renderer, file_path));
}

void ResourceManager::add_texture(
        const string keyname, const string file_path,
        uint16_t image_width, uint16_t image_height,
        uint16_t image_xoffset, uint16_t image_yoffset,
        uint16_t image_sep, SpriteAnimationType animation, float image_speed
    ) {
        textures.emplace( keyname,
            new GameSpriteInfo(
                renderer, file_path,
                image_width, image_height,
                image_xoffset, image_yoffset,
                image_sep, animation, image_speed
            )
        );
    }

void ResourceManager::add_texture(
        const string keyname, const string file_path,
        uint16_t image_width, uint16_t image_height,
        uint16_t image_xoffset, uint16_t image_yoffset,
        uint16_t image_sep, SpriteAnimationType animation, float image_speed, bool flag, Uint32 key
    ) {
        textures.emplace(
            keyname,
            new GameSpriteInfo(
                renderer, file_path,
                image_width, image_height,
                image_xoffset, image_yoffset,
                image_sep, animation, image_speed, flag, key
            )
        );
    }

void ResourceManager::add_texture(
        const string keyname, const string file_path,
        uint16_t image_width, uint16_t image_height,
        uint16_t image_xoffset, uint16_t image_yoffset,
        uint16_t image_sep, float angle_ini, float angle_span
    ) {
        textures.emplace(
            keyname,
            new GameSpriteInfo(
                renderer, file_path,
                image_width, image_height,
                image_xoffset, image_yoffset,
                image_sep, angle_ini, angle_span
            )
        );
    }

GameSpriteInfo* ResourceManager::get_sprite(const std::string idx) {
    return textures[idx];
}

SDL2pp::Font* ResourceManager::get_font(TextType type) {
    return fonts[type];
}

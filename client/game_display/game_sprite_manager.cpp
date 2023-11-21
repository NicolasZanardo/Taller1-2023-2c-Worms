#include "game_sprite_manager.h"

using namespace std;

GameSpriteManager::GameSpriteManager(SDL2pp::Renderer &renderer) :
        renderer(renderer) {}

GameSpriteManager::~GameSpriteManager() {
    for (auto [key, val]: textures) {
        delete (val);
    }
}

void GameSpriteManager::add_texture(const string keyname, const string file_path) {
    add_texture(keyname, file_path, -1, -1, 0, 0, 0, 0.0f);
}

void GameSpriteManager::add_texture(const string keyname, const string file_path,
                                    uint16_t image_width, uint16_t image_height,
                                    uint16_t image_xoffset, uint16_t image_yoffset,
                                    uint16_t image_sep, float image_speed) {
    textures.emplace(
            keyname,
            new GameSpriteInfo(
                    renderer, file_path,
                    image_width, image_height,
                    image_xoffset, image_yoffset,
                    image_sep, image_speed
            )
    );
}

void GameSpriteManager::add_texture(const string keyname, const string file_path,
                                    uint16_t image_width, uint16_t image_height,
                                    uint16_t image_xoffset, uint16_t image_yoffset,
                                    uint16_t image_sep, float image_speed, bool flag, Uint32 key) {
    textures.emplace(
            keyname,
            new GameSpriteInfo(
                    renderer, file_path,
                    image_width, image_height,
                    image_xoffset, image_yoffset,
                    image_sep, image_speed, flag, key
            )
    );
}

GameSpriteInfo *GameSpriteManager::get(const std::string idx) {
    return this->textures[idx];
}

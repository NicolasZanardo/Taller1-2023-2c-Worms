#include "sprites_manager.h"

#include <stdexcept>

SpritesManager::SpritesManager(SDL2pp::Renderer& renderer)
    : renderer(&renderer) {}

void SpritesManager::addSprite(std::string id, std::string sprite_file,
                uint16_t frame_width, uint16_t frame_height, uint16_t sep) {
    if (this->sprites.find(id) != this->sprites.end()) {
        throw std::runtime_error("The name has alredy been used by another sprite");
    }

    this->sprites.insert(
        std::pair<std::string, Sprite>(
            id,
            std::move(Sprite(*(this->renderer), sprite_file, frame_width, frame_height, sep)))
    );
}

void SpritesManager::addSprite(std::string id, std::string sprite_file,
                               uint16_t frame_width, uint16_t frame_height, uint16_t sep, bool flag, Uint32 key) {
    if (this->sprites.find(id) != this->sprites.end()) {
        throw std::runtime_error("The name has alredy been used by another sprite");
    }

    this->sprites.insert(
            std::pair<std::string, Sprite>(
                    id,
                    std::move(Sprite(*(this->renderer), sprite_file, frame_width, frame_height, sep, flag, key)))
    );
}

void SpritesManager::renderSprite(std::string id, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    Sprite& sprite = this->check_exists(id);
    sprite.render(dst, flip_type);
}

void SpritesManager::renderSprite(std::string id, const SDL2pp::Rect dst,
                                        double angle, SDL_RendererFlip &flip_type) {
    Sprite& sprite = this->check_exists(id);
    sprite.render(dst, angle, flip_type);
}

void SpritesManager::renderSprite(std::string id, uint16_t num_frame,
                                const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    Sprite& sprite = this->check_exists(id);
    sprite.render(num_frame, dst, flip_type);
}

Sprite& SpritesManager::check_exists(const std::string& id) {
    auto it = this->sprites.find(id);
    if (it == this->sprites.end()) {
        throw std::runtime_error("The sprite with this id not exists.");
    }

    return it->second;
}

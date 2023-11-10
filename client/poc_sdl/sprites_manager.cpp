#include "sprites_manager.h"

#include <stdexcept>

SpritesManager::SpritesManager(SDL2pp::Renderer& renderer)
    : renderer(&renderer) {}

void SpritesManager::addSprite(std::string id, std::string sprite_file) {
    if (this->sprites.find(id) != this->sprites.end()) {
        throw std::runtime_error("The name has alredy been used by another sprite");
    }

    this->sprites.insert(
        std::pair<std::string, Sprite>(
            id,
            std::move(Sprite(*(this->renderer), sprite_file)))
    );
}

void SpritesManager::renderSprite(std::string id, const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    auto it = this->sprites.find(id);
    if (it == this->sprites.end()) {
        throw std::runtime_error("The name has alredy been used by another sprite");
    }

    it->second.render(dst, flip_type);
}

void SpritesManager::renderSprite(std::string id, uint16_t num_frame,
                                const SDL2pp::Rect dst, SDL_RendererFlip &flip_type) {
    auto it = this->sprites.find(id);
    if (it == this->sprites.end()) {
        throw std::runtime_error("The name has alredy been used by another sprite");
    }

    it->second.render(num_frame, dst, flip_type);
}

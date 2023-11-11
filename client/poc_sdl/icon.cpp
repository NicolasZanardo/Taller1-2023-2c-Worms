#include "icon.h"

Icon::Icon(SpritesManager& sprites_manager, const std::string& id)
    : sprites_manager(&sprites_manager), id(id) {}

void Icon::render(const SDL2pp::Rect dest, bool facing_left) {
    SDL_RendererFlip flip = (this->img_looking_left != facing_left) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    this->sprites_manager->renderSprite(this->id, dest, flip);
}

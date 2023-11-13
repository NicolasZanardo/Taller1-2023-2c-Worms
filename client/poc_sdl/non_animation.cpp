#include "non_animation.h"

NonAnimation::NonAnimation(SpritesManager& sprites_manager, const std::string& id, bool img_looking_left)
    : img_looking_left(img_looking_left)
    , sprites_manager(&sprites_manager)
    , id(id) {}

void NonAnimation::render(const SDL2pp::Rect dest, double angle, bool facing_left) {
    SDL_RendererFlip flip = (this->img_looking_left != facing_left) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    this->sprites_manager->renderSprite(
        this->id,
        dest,
        angle,
        flip
    );
}

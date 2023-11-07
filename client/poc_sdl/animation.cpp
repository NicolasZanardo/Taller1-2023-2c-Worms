#include "animation.h"

Animation::Animation(SpritesManager& sprites_manager, const std::string& id,
                                        uint16_t num_frames, bool img_looking_left)
    : img_looking_left(img_looking_left)
    , elapsed(0.0f)
    , frame_selector(num_frames, 0)
    , sprites_manager(&sprites_manager)
    , id(id) {}

void Animation::update(float dt) {
    this->elapsed += dt;
    while (this->elapsed > FRAME_RATE) {
        this->frame_selector.advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}
void Animation::render(const SDL2pp::Rect dest, bool facing_left) {
    SDL_RendererFlip flip = (this->img_looking_left != facing_left) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    this->sprites_manager->renderSprite(
        this->id,
        this->frame_selector.getCurrentFrame(),
        dest,
        flip
    );
}

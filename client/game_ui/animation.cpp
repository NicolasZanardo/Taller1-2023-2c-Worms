#include "animation.h"

Animation::Animation(SpritesManager& sprites_manager, const std::string& id,
                FrameSelectorMode mode, uint16_t num_frames, bool img_looking_left)
    : img_looking_left(img_looking_left)
    , elapsed(0.0f)
    , frame_selector(mode, num_frames, 0)
    , sprites_manager(&sprites_manager)
    , id(id) {}

Animation::Animation(Animation&& other) noexcept
    : elapsed(other.elapsed)
    , frame_selector(other.frame_selector)
    , sprites_manager(other.sprites_manager)
    , id(other.id) {}

Animation& Animation::operator=(Animation&& other) noexcept {
    if (&other == this) {
		return *this;
    }

    this->elapsed = other.elapsed;
    this->frame_selector = other.frame_selector;
    this->sprites_manager = other.sprites_manager;
    this->id = other.id;

    return *this;
}

void Animation::reset() {
    this->frame_selector.reset();
}

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

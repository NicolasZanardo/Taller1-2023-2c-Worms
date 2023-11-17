#include "worm_state.h"

#include "ui_utils.h"
#include "constants.h"

WormState::WormState(SpritesManager &sprites_manager) :
        x(300), // TODO CORRECTLY INITIALIZE RECEIVING A WORMDTO
        y(300),
        state(MovementStateDto::idle),
        facingLeft(false),
        animations({
                           {MovementStateDto::idle,    std::make_shared<Animation>(
                                   sprites_manager,
                                   "wwalk",
                                   FrameSelectorMode::BOUNCE,
                                   15, true)},
                           {MovementStateDto::falling, std::make_shared<Animation>(
                                   sprites_manager,
                                   "wfall",
                                   FrameSelectorMode::STAY_LAST,
                                   2, true)},
                           {MovementStateDto::jumping, std::make_shared<Animation>(
                                   sprites_manager,
                                   "wwalk",
                                   FrameSelectorMode::BOUNCE,
                                   15, true)},
                           {MovementStateDto::walking, std::make_shared<Animation>(
                                   sprites_manager,
                                   "wwalk",
                                   FrameSelectorMode::BOUNCE,
                                   15, true)}
                   }),
        current_animation(animations[state]) {}

WormState::WormState(WormState &&other) noexcept
        : current_animation(nullptr) // TODO
{
    *this = std::move(other);  // Reuse the move assignment operator
}

WormState &WormState::operator=(WormState &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    // Move data members
    this->facingLeft = other.facingLeft;
    this->x = other.x;
    this->y = other.y;

    // Move animations map
    this->animations = std::move(other.animations);

    // Move current animation pointer
    this->current_animation = other.current_animation;

    return *this;
}

void WormState::update(WormDto &updated_data, float dt) {
    if (this->x < updated_data.x) {
        this->x = UiUtils::x_meters_pos_to_x_pixel_pos(updated_data.x);
        this->facingLeft = false;
    } else if (this->x > updated_data.x) {
        this->x = UiUtils::x_meters_pos_to_x_pixel_pos(updated_data.x);
        this->facingLeft = true;
    }

    this->y = UiUtils::y_meters_pos_to_y_pixel_pos(updated_data.y);

    if (this->state != updated_data.state) {
        auto new_anim = this->animations.at(updated_data.state);
        if (new_anim) {
            this->current_animation = new_anim;
            this->current_animation->reset();
        }
    }

    this->current_animation->update(dt);
}

void WormState::render() {
    current_animation->render(
            SDL2pp::Rect(
                    x,
                    y,
                    UiUtils::meters_to_pixels(WORM_SIZE),
                    UiUtils::meters_to_pixels(WORM_SIZE)),
            this->facingLeft
    );
}


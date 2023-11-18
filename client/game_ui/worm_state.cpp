#include "worm_state.h"

#include "ui_utils.h"
#include "constants.h"

WormState::WormState(SpritesManager &sprites_manager) :
        x(300), // TODO CORRECTLY INITIALIZE RECEIVING A WORMDTO
        y(300),
        pixel_width(UiUtils::meters_to_pixels(WORM_SIZE)),
        pixel_height(UiUtils::meters_to_pixels(WORM_SIZE)),
        state(MovementStateDto::idle),
        facingLeft(false),
        animations({
                           {MovementStateDto::idle,          std::make_shared<Animation>(
                                   sprites_manager,
                                   "wwalk",
                                   FrameSelectorMode::BOUNCE,
                                   15, true)},
                           {MovementStateDto::falling,       std::make_shared<Animation>(
                                   sprites_manager,
                                   "wfall",
                                   FrameSelectorMode::STAY_LAST,
                                   2, true)},
                           {MovementStateDto::going_upwards, std::make_shared<Animation>(
                                   sprites_manager,
                                   "wjumpu",
                                   FrameSelectorMode::STAY_LAST,
                                   10, true)},
                           {MovementStateDto::moving,        std::make_shared<Animation>(
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
    // Update x
    this->facingLeft = !updated_data.is_facing_right;
    this->x = UiUtils::x_meters_pos_to_x_pixel_pos(updated_data.x);

    // Update y
    this->y = UiUtils::y_meters_pos_to_y_pixel_pos(updated_data.y);

    // Switch anim if needed
    if (this->state != updated_data.state) {
        this->state = updated_data.state;
        auto new_anim = this->animations.at(this->state);
        if (new_anim) {
            this->current_animation = new_anim;
            this->current_animation->reset();
        }
    }

    // TODO DELETE
    /* switch (state) {
        case MovementStateDto::idle:
            std::cout << "idle" << std::endl;
            break;
        case MovementStateDto::moving:
            std::cout << "moving" << std::endl;
            break;
        case MovementStateDto::going_upwards:
            std::cout << "going_upwards" << std::endl;
            break;
        case MovementStateDto::falling:
            std::cout << "falling" << std::endl;
            break;
        default:
            std::cout << "unknown" << std::endl;
            break;
    }*/


    // Update anim
    if (this->state != MovementStateDto::idle) {
        this->current_animation->update(dt);
    }
}

void WormState::render() {

    current_animation->render(
            SDL2pp::Rect(
                    x - (pixel_width / 2),
                    y - (pixel_height / 2),
                    pixel_width,
                    pixel_height),
            this->facingLeft
    );
}


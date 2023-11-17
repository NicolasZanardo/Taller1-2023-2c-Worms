#include "worm_state.h"

#include "client_game_state.h"

WormState::WormState(SpritesManager& sprites_manager)
    : x(300), y(300)
    , state(MovementStateDto::idle)
    , facingLeft(false)
    , animations({
        {MovementStateDto::idle, std::make_shared<Animation>(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 15,  true)},
        {MovementStateDto::falling, std::make_shared<Animation>(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 15,  true)},
        {MovementStateDto::jumping,std::make_shared<Animation>(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 15, true)},
        {MovementStateDto::walking, std::make_shared<Animation>(sprites_manager, "wwalk",FrameSelectorMode::BOUNCE, 15,  true)}
    })
    , current_animation(animations[state]) {}

WormState::WormState(WormState&& other) noexcept
        : current_animation(nullptr) // TODO
{
    *this = std::move(other);  // Reuse the move assignment operator
}

WormState& WormState::operator=(WormState&& other) noexcept {
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

void WormState::update(WormDto& updated_data, float dt) {
    if (this->x < updated_data.x) {
        this->x = updated_data.x * 25;
        this->facingLeft = false;
    } else if (this->x > updated_data.x) {
        this->x = updated_data.x * 25;
        this->facingLeft = true;
    }

    this->y = 575 - updated_data.y * 25; // (Screen height - 25 offset ) - (x converted to pixels)

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
    current_animation->render(SDL2pp::Rect(x, y, 50, 50), this->facingLeft);
}

// void WormState::moveRigth() {
//     moving = true;
//     facingLeft = false;
// }

// void WormState::moveLeft() {
//     moving = true;
//     facingLeft = true;
// }

// void WormState::stopMoving() {
//     moving = false;
// }

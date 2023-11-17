#include "worm_state.h"

#include "client_game_state.h"

WormState::WormState(SpritesManager& sprites_manager) :
    // : an(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 12, true)
    facingLeft(false)
    , x(300), y(300)
    , animations({
        {MovementStateDto::idle, std::make_shared<Animation>(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 15,  true)},
        {MovementStateDto::jumping,std::make_shared<Animation>(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 15, true)},
        {MovementStateDto::walking, std::make_shared<Animation>(sprites_manager, "wwalk",FrameSelectorMode::BOUNCE, 15,  true)}
    }) {}

WormState::WormState(WormState&& other) noexcept
        : current_animation(nullptr) // TODO
{
    std::cout << "worm state move constructor\n";
    *this = std::move(other);  // Reuse the move assignment operator
}

WormState& WormState::operator=(WormState&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    // this->current_animation = nullptr;  // Ensure proper cleanup

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
        this->x = updated_data.x;
        this->facingLeft = false;
    } else if (this->x > updated_data.x) {
        this->x = updated_data.x;
        this->facingLeft = true;
    }

    this->y = updated_data.y;

    if (this->state != updated_data.state) {
        this->current_animation = this->animations.at(updated_data.state);
        this->current_animation->reset();
    }

    this->current_animation->update(dt);
}

void WormState::render() {
    current_animation->render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
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

#include "worm_state.h"

#include "client_game_state.h"

WormState::WormState(SpritesManager& sprites_manager)
    : an(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 12, true)
    , facingLeft(false)
    , moving(false)
    , x(300), y(300) {}

WormState::WormState(WormState&& other)
    : an(std::move(an))
    , facingLeft(other.facingLeft)
    , moving(other.moving)
    , x(other.x), y(other.x) {std::cout << "worm state move consturctor\n";}

WormState& WormState::operator=(WormState&& other) {
    if (this == &other) {
        return *this;
    }

    this->an = std::move(other.an);
    this->facingLeft = other.facingLeft;
    this->moving = other.moving;
    this->x = x;
    this->y = y;

    return *this;
}

void WormState::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void WormState::render() {
    an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
}

void WormState::moveRigth() {
    moving = true;
    facingLeft = false;
}

void WormState::moveLeft() {
    moving = true;
    facingLeft = true;
}

void WormState::stopMoving() {
    moving = false;
}

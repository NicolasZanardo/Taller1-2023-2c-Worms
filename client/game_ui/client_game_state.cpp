#include "client_game_state.h"

ClientGameState::ClientGameState(SpritesManager& sprites_manager)
    : an(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 12, true)
    , facingLeft(false)
    , moving(false)
    , x(300), y(300) {}

void ClientGameState::update(float dt) {
    if (moving) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else
            x += 3;
    }
}

void ClientGameState::render() {
    an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
}

void ClientGameState::moveRigth() {
    moving = true;
    facingLeft = false;
}

void ClientGameState::moveLeft() {
    moving = true;
    facingLeft = true;
}

void ClientGameState::stopMoving() {
    moving = false;
}

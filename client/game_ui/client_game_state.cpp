#include "client_game_state.h"

// ClientGameState::ClientGameState(SpritesManager& sprites_manager)
//     : an(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 12, true)
//     , facingLeft(false)
//     , moving(false)
//     , x(300), y(300) {}

ClientGameState::ClientGameState(SpritesManager& sprites_manager)
    : sprites_manager(&sprites_manager)
    , worms()
    , worm_state(sprites_manager) {}

void ClientGameState::load() {
    // this->worms.emplace(std::make_pair(1, WormState(*(this->sprites_manager))));

    std::cout << "loading\n";
    this->worms.emplace(
        std::make_pair<std::string, WormState>(
            std::string("hola"),
            std::move(WormState(*(this->sprites_manager)))
        )
    );
    std::cout << "loaded\n";
}

void ClientGameState::update(float dt) {
    // if (moving) {
    //     an.update(dt);
    //     if (facingLeft)
    //         x -= 3;
    //     else
    //         x += 3;
    // }
    worm_state.update(dt);
    // this->worms[1].update(dt);
}


void ClientGameState::render() {
    // an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
    worm_state.render();
    // this->worms[1].render();
}

void ClientGameState::moveRigth() {
    // moving = true;
    // facingLeft = false;
    worm_state.moveRigth();
    // this->worms[1].moveRigth();
}

void ClientGameState::moveLeft() {
    // moving = true;
    // facingLeft = true;
    worm_state.moveLeft();
    // this->worms[1].moveLeft();
}

void ClientGameState::stopMoving() {
    // moving = false;
    worm_state.stopMoving();
    // this->worms[1].stopMoving();
}

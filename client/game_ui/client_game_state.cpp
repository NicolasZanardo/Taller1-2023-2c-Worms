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

    // std::cout << "loading\n";
    // this->worms.emplace(
    //     std::make_pair<int, WormState>(
    //         id,
    //         std::move(WormState(*(this->sprites_manager)))
    //     )
    // );
    // std::cout << "loaded\n";
}

void ClientGameState::update(std::unique_ptr<ClientGameStateDTO> game_state_dto, float dt) {
    this-> game_remaining_time = game_state_dto.game_remaining_time;
    this-> turn_remaining_time = game_state_dto.turn_remaining_time;
    
    for (auto& worm_state : game_state_dto->worms) {
        this->worms_state[worm.entity_id].update(worm_state, dt);
    }

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
    this->beam_state.render();
    this->worm_state.render();
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

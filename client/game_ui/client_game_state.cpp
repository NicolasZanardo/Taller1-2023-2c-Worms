#include "client_game_state.h"

// ClientGameState::ClientGameState(SpritesManager& sprites_manager)
//     : an(sprites_manager, "wwalk", FrameSelectorMode::BOUNCE, 12, true)
//     , facingLeft(false)
//     , moving(false)
//     , x(300), y(300) {}

ClientGameState::ClientGameState(SpritesManager& sprites_manager)
    : sprites_manager(&sprites_manager)
    , worms_state() {}

void ClientGameState::load(std::shared_ptr<ClientGameStateDTO> game_state_dto) {
    std::cout << "Loading scenario\n";

    this->width = game_state_dto->width;
    this->height = game_state_dto->height;

    std::cout << "w: " << width << " - h: " << height << '\n';
    std::cout << "worms in dto: " << game_state_dto->worms.size() << '\n';

    for (auto& worm_state_dto : game_state_dto->worms) {
        this->worms_state.emplace(worm_state_dto.entity_id, *(this->sprites_manager));
    }

    std::cout << "worms populated\n";
}

void ClientGameState::update(std::shared_ptr<ClientGameStateDTO> game_state_dto, float dt) {
    this-> game_remaining_time = game_state_dto->remaining_game_time;
    this-> turn_remaining_time = game_state_dto->remaining_turn_time;
    
    for (auto& worm_state_dto : game_state_dto->worms) {
        auto it = this->worms_state.find(worm_state_dto.entity_id);
        if (it != this->worms_state.end()) {
            it->second.update(worm_state_dto, dt);
        }
        // this->worms_state[worm_state_dto.entity_id].update(worm_state_dto, dt);
    }

    std::cout << "Show pos\n";
    for (auto& worm : this->worms_state) {
        std::cout << "x: " << worm.second.x << "- y: " << worm.second.y << '\n';
    }

    // if (moving) {
    //     an.update(dt);
    //     if (facingLeft)
    //         x -= 3;
    //     else
    //         x += 3;
    // }
    // worm_state.update(dt);
    // this->worms[1].update(dt);
}


void ClientGameState::render() {
    // an.render(SDL2pp::Rect(x, y, 200, 200), this->facingLeft);
    // for (auto& beam : this->beams_state) { beam.render(); }
    std::cout << "init render worms\n";
    for (auto& worm : this->worms_state) { worm.second.render(); }
    std::cout << "end render worms\n";
    // this->worms[1].render();
}

void ClientGameState::moveRigth() {
    // moving = true;
    // facingLeft = false;
    // worm_state.moveRigth();
    // this->worms[1].moveRigth();
}

void ClientGameState::moveLeft() {
    // moving = true;
    // facingLeft = true;
    // worm_state.moveLeft();
    // this->worms[1].moveLeft();
}

void ClientGameState::stopMoving() {
    // moving = false;
    // worm_state.stopMoving();
    // this->worms[1].stopMoving();
}

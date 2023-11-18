#include "client_game_state.h"

ClientGameState::ClientGameState(SpritesManager& sprites_manager)
    : sprites_manager(&sprites_manager)
    , worms_state() {}

void ClientGameState::load(std::shared_ptr<ClientGameStateDTO> game_state_dto) {
    std::cout << "Loading scenario\n";

    this->width = game_state_dto->width;
    this->height = game_state_dto->height;

    for (auto& worm_state_dto : game_state_dto->worms) {
        this->worms_state.emplace(worm_state_dto.entity_id, *(this->sprites_manager));
        this->worms_state.at(worm_state_dto.entity_id).update(worm_state_dto, 0); // TODO 0 dt on load?
    }

    for (auto& beam_state_dto : game_state_dto->beams) {
        this->beams_state.emplace_back(*(this->sprites_manager), beam_state_dto);
    }

}

void ClientGameState::update(std::shared_ptr<ClientGameStateDTO> game_state_dto, float dt) {
    this-> game_remaining_time = game_state_dto->remaining_game_time;
    this-> turn_remaining_time = game_state_dto->remaining_turn_time;
    
    for (auto& worm_state_dto : game_state_dto->worms) {
        auto it = this->worms_state.find(worm_state_dto.entity_id);
        if (it != this->worms_state.end()) {
            it->second.update(worm_state_dto, dt);
        }
    }
}


void ClientGameState::render() {
    for (auto& beam : this->beams_state) { beam.render(); }
    for (auto& worm : this->worms_state) { worm.second.render(); }
}

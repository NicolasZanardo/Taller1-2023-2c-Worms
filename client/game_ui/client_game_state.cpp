#include "client_game_state.h"
#include "ui_utils.h"
#include "constants.h"

ClientGameState::ClientGameState(GameDisplay& display)
    : display(display)
    , worms() {}

void ClientGameState::load(std::shared_ptr<ClientGameStateDTO> game_state_dto) {
    std::cout << "Loading scenario size("
        << game_state_dto->width << ","
        << game_state_dto->height << ")"
        << "   Beams: " << game_state_dto->beams.size()
        << "   Worms: " << game_state_dto->worms.size() << "\n";

    width = game_state_dto->width;
    height = game_state_dto->height;

    for (auto& beam : game_state_dto->beams) {
        float beam_w = 0, beam_h = 0;
        switch (beam.type) {
            case BeamDto::Type::LONG:
                beam_w = LARGE_BEAM_WIDTH;
                beam_h = LARGE_BEAM_HEIGHT;
                break;
            case BeamDto::Type::SHORT:
                beam_w = SHORT_BEAM_WIDTH;
                beam_h = SHORT_BEAM_HEIGHT;
                break;
        }

        auto image = display.new_sprite("beam_large", beam_w, beam_h, beam.angle);
        image->set_pos(beam.x+0.6f, beam.y+0.1f);
    }

    for (auto& worm : game_state_dto->worms) {
        worms.emplace(worm.entity_id, std::make_shared<WormEntity>(display, worm));
        display.camera.set_target(worms[worm.entity_id].get());
    }

}

void ClientGameState::update(std::shared_ptr<ClientGameStateDTO> game_state_dto) {
    game_remaining_time = game_state_dto->remaining_game_time;
    turn_remaining_time = game_state_dto->remaining_turn_time;
    
    for (auto& worm_dto : game_state_dto->worms) {
        auto& it = worms[worm_dto.entity_id];
        it->update(worm_dto);
    }
}

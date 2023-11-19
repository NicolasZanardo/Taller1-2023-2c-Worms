#include "client_game_state.h"
#include "ui_utils.h"
#include "constants.h"

ClientGameState::ClientGameState(GameDisplay& display)
    : display(display)
    , worms() {}

void ClientGameState::load(std::shared_ptr<ClientGameStateDTO> game_state_dto) {
    std::cout << "Loading scenario\n";

    width = game_state_dto->width;
    height = game_state_dto->height;

    for (auto& worm : game_state_dto->worms) {
        worms.emplace(worm.entity_id, std::make_shared<WormEntity>(display, worm));
    }

    for (auto& beam : game_state_dto->beams) {
        float beam_w = 0;
        switch (beam.type) {
            case BeamDto::Type::LONG:
                beam_w = UiUtils::meters_to_pixels(LARGE_BEAM_WIDTH);
                break;
            case BeamDto::Type::SHORT:
                beam_w = UiUtils::meters_to_pixels(SHORT_BEAM_WIDTH);
                break;
        }

        auto image = display.new_sprite("beam_large", beam_w, 24, beam.angle);
        image->set_pos(
            UiUtils::x_meters_pos_to_x_pixel_pos(beam.x),
            UiUtils::y_meters_pos_to_y_pixel_pos(beam.y)
        );

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

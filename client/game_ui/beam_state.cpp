#include "beam_state.h"
#include "ui_utils.h"
#include "constants.h"

BeamState::BeamState(SpritesManager& sprites_manager, BeamDto& beam_dto)
    : sprites_manager(&sprites_manager),
      non_animation(sprites_manager, "beam_large", true), // TODO Esta hardcoded el beam long
      x(UiUtils::x_meters_pos_to_x_pixel_pos(beam_dto.x)),
      y(UiUtils::y_meters_pos_to_y_pixel_pos(beam_dto.y)),
      angle(beam_dto.angle){
    _set_dimens(beam_dto.type);
}

void BeamState::render() {
    SDL2pp::Rect dest(this->x, this->y, width, height);
    this->non_animation.render(dest, this->angle, true);
}

void BeamState::_set_dimens(BeamDto::Type type) {
    switch (type) {
        case BeamDto::Type::LONG: {
            height = UiUtils::meters_to_pixels(LARGE_BEAM_HEIGHT);
            width = UiUtils::meters_to_pixels(LARGE_BEAM_WIDTH);
            return;
        }

        case BeamDto::Type::SHORT: {
            height = UiUtils::meters_to_pixels(SHORT_BEAM_HEIGHT);
            width = UiUtils::meters_to_pixels(SHORT_BEAM_WIDTH);
            return;
        }
    }
}
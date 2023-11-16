#include "beam_state.h"

BeamState::BeamState(SpritesManager& sprites_manager, BeamDto& beam_dto)
    : sprites_manager(&sprites_manager), // TODO
      non_animation(sprites_manager, "ACA VA EL SPRITE DEL BEAM", true),
      x(beam_dto.x),
      y(beam_dto.y),
      angle(beam_dto.angle),
      type(beam_dto.type){
    // inicializar estado con el dto
}

void BeamState::render() {
    float beamHeight = 0.8f * 25;
    float beamWidth;
    if (this->type == BeamDto::Type::LONG) {
        beamWidth = 6.0f * 25; // TODO 0.8 is beam height have a constant in common or passed height, width on dto, 25 is the constat for pixels
    } else {
        beamWidth = 3.0f * 25;
    }

    SDL2pp::Rect dest(this->x, this->y, beamWidth, beamHeight);
    this->non_animation.render(dest, this->angle, false);
}

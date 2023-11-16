#include "beam_state.h"

BeamState::BeamState(SpritesManager& sprites_manager, beamDto& beam_dto)
    : sprites_manager(&sprites_manager) {
    // inicializar estado con el dto
}

void BeamState::render() {
    SDL2pp::Rect dest(this->x, this->y, /*width, height*/);
    this->non_animation.render(const SDL2pp::Rect dest, this->angle, false);
}

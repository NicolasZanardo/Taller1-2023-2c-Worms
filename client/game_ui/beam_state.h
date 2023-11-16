#ifndef __BEAM_STATE_H__
#define __BEAM_STATE_H__

#include "non_animation.h"
#include "sprites_manager.h"
#include "Game/beamDto.h"

class BeamState {
public:
    BeamState() = delete;
    explicit BeamState(SpritesManager& sprites_manager, BeamDto& beam_dto);
    ~BeamState() = default;

    // BeamState(BeamState&& other);
    // BeamState& operator=(BeamState&& other);

    // void updateCamera(Camera);
    void render();

private:
    SpritesManager* sprites_manager;
    NonAnimation non_animation;

    float x;
    float y;
    float angle;
    BeamDto::Type type;
};

#endif  // __BEAM_STATE_H__

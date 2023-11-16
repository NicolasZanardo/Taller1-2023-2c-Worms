#ifndef __BEAM_STATE_H__
#define __BEAM_STATE_H__

#include "non_animation.h"
#include "sprites_manager.h"

#include "beamDto.h"

class BeamState {
public:
    BeamState() = delete;
    explicit BeamState(SpritesManager& sprites_manager, beamDto& beam_dto);
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
};

#endif  // __BEAM_STATE_H__

#ifndef TP_WORMS_CONSTANTS_H
#define TP_WORMS_CONSTANTS_H

#include <string>

// DIMENS
const float WORM_SIZE = 1.0f;
const float CLIENT_FPS = 25.0f;

const float BEAMS_HEIGHT = 0.8f;
const float LARGE_BEAM_WIDTH = 6.0f;
const float LARGE_BEAM_HEIGHT = BEAMS_HEIGHT;
const float SHORT_BEAM_WIDTH = 3.0f;
const float SHORT_BEAM_HEIGHT = BEAMS_HEIGHT;
const float MAX_BEAM_WALKABLE_ANGLE = 45.0f;

const float INITIAL_PROJECTILE_IMPULSE = 20;
const float INITIAL_PROJECTILE_IMPULSE_X = INITIAL_PROJECTILE_IMPULSE;
const float INITIAL_PROJECTILE_IMPULSE_y = INITIAL_PROJECTILE_IMPULSE;
const float PROJECTILE_DENSITY = 1.2f;
const float PROJECTILE_RADIUS = 0.2f;
const float FRAGMENT_RADIUS = 0.15f;
const float SHOT_OFFSET_FROM_WORM = (WORM_SIZE / 2) + PROJECTILE_RADIUS * 2;

const float WATER_HEIGHT = 6;

const int COLOR_BY_CLIENT[] = {
    0xFF6969,0x69FFFF,0x87FF69,0xE169FF,0xE1FF69,0x8769FF
};

const std::string NAME_BY_CLIENT[] = {
    "rojo","azul","verde","violeta","amarillo","jose"
};

#endif

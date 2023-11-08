#ifndef SERVER_GAMEMAP_H
#define SERVER_GAMEMAP_H

#include <list>

enum BeamType {
    SHORT, LARGE
};

struct BeamOnMapDto {
    float x;
    float y;
    float angle;
    BeamType type;
};

struct WormOnMapDto {
    float x;
    float y;
};


struct GameScenario {
    std::list<BeamOnMapDto> beams;
    std::list<WormOnMapDto> worms;
};

#endif
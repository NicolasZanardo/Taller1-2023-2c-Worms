#ifndef SERVER_GAMEMAP_H
#define SERVER_GAMEMAP_H

#include <vector>
#include "WormScenarioData.h"
#include "BeamScenarioData.h"


struct GameScenarioData { // TODO Have in server package
    float room_width;
    float room_height;
    std::vector<BeamScenarioData> beams;
    std::vector<WormScenarioData> worms;

};

#endif
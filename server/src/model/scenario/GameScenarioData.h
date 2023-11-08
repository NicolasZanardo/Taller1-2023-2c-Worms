#ifndef SERVER_GAMEMAP_H
#define SERVER_GAMEMAP_H

#include <list>
#include "BeamScenarioData.h"
#include "WormScenarioData.h"


struct GameScenarioData {
    std::vector<BeamScenarioData> beams;
    std::vector<WormScenarioData> worms;
};

#endif
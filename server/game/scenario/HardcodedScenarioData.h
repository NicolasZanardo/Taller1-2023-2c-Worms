#ifndef SERVER_HARDCODEDSCENARIO_H
#define SERVER_HARDCODEDSCENARIO_H

#include "GameScenarioData.h"

class HardcodedScenarioData {
public:
    static GameScenarioData get() {
        GameScenarioData scenario;
        scenario.room_height = 40;
        scenario.room_width = 80;
        scenario.water_height_level = 12;
        // Populate large beams next to each other at y=0
        float i = 0;
        scenario.beams.emplace_back(18.9, 15.7f, -12.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f, 00.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f, 10.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f,350.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f, 35.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f,325.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f, 45.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(i++ * 6.0f + 23.0f, 13.0f, 90.0f, BeamScenarioData::Type::LONG);
        scenario.beams.emplace_back(27.0f, 16.0f, 10.0f, BeamScenarioData::Type::LONG);
        // Populate large beams at y=1 in the middle of the scenario


        // Populate worms on each side of the map
        scenario.worms.emplace_back(24.0f, 18.0f);
        scenario.worms.emplace_back(27.0f, 18.0f);
        scenario.worms.emplace_back(30.0f, 18.0f);
        scenario.worms.emplace_back(33.0f, 18.0f);
        scenario.worms.emplace_back(36.0f, 18.0f);
        return scenario;
    }
};

#endif

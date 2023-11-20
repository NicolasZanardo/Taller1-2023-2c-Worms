#ifndef SERVER_HARDCODEDSCENARIO_H
#define SERVER_HARDCODEDSCENARIO_H

#include "GameScenarioData.h"

class HardcodedScenarioData {
public:
    static GameScenarioData get() {
        GameScenarioData scenario;
        scenario.room_height = 40;
        scenario.room_width = 36;
        // Populate large beams next to each other at y=0
        for (int i = 0; i < 6; i++) {
            scenario.beams.emplace_back(
                    i * 6 + (3), // x
                    1.0f, // y
                    0.0f, // angle
                    BeamScenarioData::Type::LONG
            );
        }

        // Populate large beams at y=1 in the middle of the scenario
        /*for (int i = 0; i < 2; i++) {
            scenario.beams.emplace_back(
                    10.0f + i * 2.0f, // x
                    1.0f, // y
                    0.0f, // angle
                    BeamScenarioData::Type::LONG
            );
        }*/

        // Populate worms on each side of the map
        scenario.worms.emplace_back(2.0f, 8.0f);
        scenario.worms.emplace_back(6.0f, 8.0f);
        scenario.worms.emplace_back(10.0f, 8.0f);
        scenario.worms.emplace_back(14.0f, 8.0f);
        return scenario;
    }
};

#endif

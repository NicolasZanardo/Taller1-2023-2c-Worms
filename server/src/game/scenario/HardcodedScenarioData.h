#ifndef SERVER_HARDCODEDSCENARIO_H
#define SERVER_HARDCODEDSCENARIO_H

#include "GameScenarioData.h"

class HardcodedScenarioData {
public:
    static GameScenarioData get() {
        GameScenarioData scenario;
        scenario.room_height = 40;
        scenario.room_width = 80;
        // Populate large beams next to each other at y=0
        for (int i = 0; i < 10; i++) {
            scenario.beams.emplace_back(
                    i * 2.0f, // x
                    0.0f, // y
                    0.0f, // angle
                    BeamScenarioData::Type::LONG
            );
        }

        // Populate large beams at y=1 in the middle of the scenario
        for (int i = 0; i < 2; i++) {
            scenario.beams.emplace_back(
                    10.0f + i * 2.0f, // x
                    1.0f, // y
                    0.0f, // angle
                    BeamScenarioData::Type::LONG
            );
        }

        // Populate worms on each side of the map
        scenario.worms.emplace_back(1.0f, 2.5f);
        scenario.worms.emplace_back(3.0f, 2.5f);
        scenario.worms.emplace_back(7.0f, 2.5f);
        scenario.worms.emplace_back(9.0f, 2.5f);
        return scenario;
    }
};

#endif

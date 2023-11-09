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
            BeamDto beam = BeamDto(
                    i * 2.0f, // x
                    0.0f, // y
                    0.0f, // angle
                    BeamDto::Type::LONG
            );

            scenario.beams.push_back(beam);
        }

        // Populate large beams at y=1 in the middle of the scenario
        for (int i = 0; i < 2; i++) {
            BeamDto beam(
                    10.0f + i * 2.0f, // x
                    1.0f, // y
                    0.0f, // angle
                    BeamDto::Type::LONG
                    );
            scenario.beams.push_back(beam);
        }

        // Populate worms on each side of the map
        WormScenarioData worm1;
        worm1.x = 1.0f;
        worm1.y = 0.0f;
        scenario.worms.push_back(worm1);

        WormScenarioData worm2;
        worm2.x = 3.0f;
        worm2.y = 0.0f;
        scenario.worms.push_back(worm2);

        WormScenarioData worm3;
        worm3.x = 7.0f;
        worm3.y = 0.0f;
        scenario.worms.push_back(worm3);

        WormScenarioData worm4;
        worm4.x = 9.0f;
        worm4.y = 0.0f;
        scenario.worms.push_back(worm4);
    }
};

#endif

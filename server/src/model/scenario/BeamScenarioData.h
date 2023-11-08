#ifndef SERVER_BEAMSCENARIODATA_H
#define SERVER_BEAMSCENARIODATA_H

enum BeamType {
    SHORT, LARGE
};

struct BeamScenarioData {
    float x;
    float y;
    float angle;
    BeamType type;
};

#endif

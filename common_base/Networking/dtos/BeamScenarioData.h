#ifndef SERVER_BEAMSCENARIODATA_H
#define SERVER_BEAMSCENARIODATA_H

enum class BeamType: uint8_t {
    SHORT = 0x00,
    LARGE = 0x01
};

struct BeamScenarioData {
    float x;
    float y;
    float angle;
    BeamType type;
};

#endif

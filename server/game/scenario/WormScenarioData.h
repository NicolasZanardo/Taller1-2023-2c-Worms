#ifndef SERVER_WORMSCENARIODATA_H
#define SERVER_WORMSCENARIODATA_H

struct WormScenarioData {
    float x;
    float y;

    WormScenarioData() : x(0.0f), y(0.0f) {}
    WormScenarioData(float x, float y) : x(x), y(y) {}

};

#endif

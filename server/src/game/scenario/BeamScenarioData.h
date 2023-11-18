#ifndef SERVER_BEAMSCENARIODATA_H
#define SERVER_BEAMSCENARIODATA_H

#include "../../../../common_base/Game/beamDto.h"

struct BeamScenarioData {
    enum class Type : uint8_t {
        SHORT = 0x00,
        LONG = 0x01
    };

    float x;
    float y;
    float angle;
    Type type;

    BeamScenarioData(
            float x,
            float y,
            float angle,
            Type type
    ) :
            x(x),
            y(y),
            angle(angle),
            type(type)
    {}

    BeamDto toBeamDto() const{
        return { x, y, angle, BeamDto::Type(type)};
    }

};

#endif

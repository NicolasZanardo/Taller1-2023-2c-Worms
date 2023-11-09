#ifndef COMMON_BEAM_H_
#define COMMON_BEAM_H_
#include <cstdint>

struct BeamDto {
    enum class Type : uint8_t {
        SHORT = 0x00,
        LONG = 0x01
    };

    float x;
    float y;
    float angle;
    Type type;

    BeamDto(
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
};
#endif

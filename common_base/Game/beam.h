#ifndef COMMON_BULLET_H_
#define COMMON_BULLET_H_
#include <cstdint>

struct Beam {
    enum class Type : uint8_t {
        SHORT = 0x00,
        LONG = 0x01
    };

    float x;
    float y;
    float angle;
    Type type;

    Beam(
        float x,
        float y,
        float angle,
        Type type
    );
};
#endif

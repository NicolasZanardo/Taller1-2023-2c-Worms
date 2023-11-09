#ifndef COMMON_BULLET_H_
#define COMMON_BULLET_H_
#include <cstdint>

struct Bullet {
    enum class Type : uint8_t {
        none = 0x00,
        bazooka = 0x01
    };

    int entity_id;
    float x;
    float y;
    float angle;
    Type type;

    Bullet(
        int entity_id,
        float x,
        float y,
        float angle,
        Type type
    ) :
    entity_id(entity_id),
    x(x), y(y), angle(angle),
    type(type) 
    {}
};
#endif

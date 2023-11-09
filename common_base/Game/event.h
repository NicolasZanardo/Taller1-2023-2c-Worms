#ifndef COMMON_WORLD_EVENT_H_
#define COMMON_WORLD_EVENT_H_
#include <cstdint>


struct WorldEvent {
    enum class Type : uint8_t {
        help_box = 0x00,
        explosion_1 = 0x01,
    };

    int entity_id;
    float x;
    float y;
    Type type;

    WorldEvent(
        int entity_id,
        float x,
        float y,
        Type type
    ) : 
    entity_id(entity_id),
    x(x), y(y), type(type) 
    {};
};
#endif

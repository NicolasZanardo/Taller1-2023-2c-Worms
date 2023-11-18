#ifndef COMMON_WORM_DTO_H_
#define COMMON_WORM_DTO_H_
#include <cstdint>

enum class MovementStateDto : uint8_t {
    idle    = 0x00,
    moving = 0x01,
    going_upwards = 0x02,
    falling = 0x03,
};

struct WormDto {

    int client_id;
    int entity_id;
    float x;
    float y;
    bool is_facing_right;
    int life;
    MovementStateDto state;

    WormDto(
            int client_id,
            int entity_id,
            float x,
            float y,
            bool is_facing_right,
            int life,
            MovementStateDto state
    ) : 
    client_id(client_id),
    entity_id(entity_id),
    x(x), y(y),
    is_facing_right(is_facing_right),
    life(life),
    state(state) 
    {}

};
#endif

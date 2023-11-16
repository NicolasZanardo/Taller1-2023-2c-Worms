#ifndef COMMON_WORM_DTO_H_
#define COMMON_WORM_DTO_H_
#include <cstdint>

enum class MovementState : uint8_t {
    idle    = 0x00,
    walking = 0x01,
    jumping = 0x02,
    shooting= 0x03,
    falling = 0x05,
};

struct WormDto {

    int client_id;
    int entity_id;
    float x;
    float y;
    int life;
    MovementState state;

    WormDto(
            int client_id,
            int entity_id,
            float x,
            float y,
            int life,
            MovementState state
    ) : 
    client_id(client_id),
    entity_id(entity_id),
    x(x), y(y), life(life),
    state(state) 
    {}

};
#endif

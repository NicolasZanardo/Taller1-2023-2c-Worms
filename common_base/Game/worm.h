#ifndef COMMON_WORM_H_
#define COMMON_WORM_H_
#include <cstdint>

// TODO: servidor o cliente?
//enum class Facing : uint8_t {
//    left  = 0x00,
//    right = 0x01
//};

struct Worm {
    enum class State : uint8_t {
        idle    = 0x00,
        walking = 0x01,
        jumping = 0x02,
        shooting= 0x03,
        dead    = 0x04,
        falling = 0x05,
        damaged = 0x06
    };

    int client_id;
    int entity_id;
    float x;
    float y;
    int life;
    State state;

    Worm(
        int client_id,
        int entity_id,
        float x,
        float y,
        int life,
        State state
    ) : 
    client_id(client_id),
    entity_id(entity_id),
    x(x), y(y), life(life),
    state(state) 
    {}

    
};
#endif

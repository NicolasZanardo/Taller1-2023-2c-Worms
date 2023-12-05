#ifndef COMMON_WORM_DTO_H_
#define COMMON_WORM_DTO_H_
#include <cstdint>
#include "WeaponTypeDto.h"

enum class WormStateDto : uint8_t {
    IDLE    = 0x00,
    MOVING = 0x01,
    JUMPING = 0x02,
    FALLING = 0x03,
    SINKING = 0x04,
    DEAD = 0x05
};

struct WormDto {

    int client_id;
    int entity_id;
    float x;
    float y;
    float angle;
    bool is_facing_right;
    int life;
    WormStateDto movement_state;
    WeaponTypeDto weapon_hold;
    float aiming_angle;

    WormDto(
        int client_id,
        int entity_id,
        float x,
        float y,
        float angle,
        bool is_facing_right,
        int life,
        WormStateDto state,
        WeaponTypeDto weapon_hold,
        float aiming_angle //  TODO maybe weapon_charged_amount later
    ) :
        client_id(client_id),
        entity_id(entity_id),
        x(x), y(y), angle(angle),
        is_facing_right(is_facing_right),
        life(life),
        movement_state(state) ,
        weapon_hold(weapon_hold),
        aiming_angle(aiming_angle)
    {}

};
#endif

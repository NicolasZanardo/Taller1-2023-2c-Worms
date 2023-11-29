#ifndef TP_WORMS_GAMESTATE_H
#define TP_WORMS_GAMESTATE_H

#include "wormDto.h"
#include "ProjectileDto.h"

struct GameState {
    int current_turn_client_id;
    int current_turn_worm_id;
    int focused_entity_id;
    float wind_speed;
    float remaining_game_time;
    float remaining_turn_time;

    GameState(
        int current_client_turn_id,
        int current_turn_worm_id,
        int focused_entity_id,
        float wind_speed,
        float remaining_game_time,
        float remaining_turn_time
    ) : current_turn_client_id(current_client_turn_id),
        current_turn_worm_id(current_turn_worm_id),
        focused_entity_id(focused_entity_id),
        wind_speed(wind_speed),
        remaining_game_time(remaining_game_time),
        remaining_turn_time(remaining_turn_time) {}
};

#endif //TP_WORMS_GAMESTATE_H

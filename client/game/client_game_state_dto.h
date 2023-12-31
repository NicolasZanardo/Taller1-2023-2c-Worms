#ifndef __CLIENT_GAME_STATE_DTO_H__
#define __CLIENT_GAME_STATE_DTO_H__

#include <vector>
#include "Game/wormDto.h"
#include "Game/beamDto.h"
#include "Game/ProjectileDto.h"
#include "Game/eventDto.h"
#include "Game/ExplosionDto.h"

class ClientGameStateDTO {
public:
    ClientGameStateDTO() = default;
    ~ClientGameStateDTO() = default;

    bool ended;
    int winner;

    float width;
    float height;
    float water_level_height;
    std::vector<int> client_ids_turn_order;

    int current_turn_client_id;
    int current_turn_worm_id;
    int focused_entity_id;
    
    float wind_speed;
    int remaining_game_time;
    int remaining_turn_time;
    
    std::vector<WormDto> worms;
    std::vector<BeamDto> beams;
    std::vector<ProjectileDto> projectiles;
    std::vector<WorldEventDto> events;
    std::vector<ExplosionDto> explosions;

    // const float scale;
    // const float xoffset;
    // const float yoffset;
};


#endif

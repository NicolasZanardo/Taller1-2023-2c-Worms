#ifndef __CLIENT_GAME_STATE_DTO_H__
#define __CLIENT_GAME_STATE_DTO_H__

#include <vector>
#include "Game/wormDto.h"
#include "Game/beamDto.h"
#include "Game/bulletDto.h"
#include "Game/eventDto.h"

class ClientGameStateDTO {
public:
    ClientGameStateDTO() = default;
    ~ClientGameStateDTO() = default;

    float width;
    float height;

    int active_client_id;
    int active_entity_id;
    
    float wind_speed; // positivo o negativo
    float remaining_game_time;
    float remaining_turn_time;
    
    std::vector<WormDto> worms;
    std::vector<BeamDto> beams;
    std::vector<ProjectileDto> projectiles;
    std::vector<WorldEventDto> events;

    // const float scale;
    // const float xoffset;
    // const float yoffset;
};


#endif

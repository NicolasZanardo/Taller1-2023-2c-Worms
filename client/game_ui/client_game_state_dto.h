#ifndef __CLIENT_GAME_STATE_DTO_H__
#define __CLIENT_GAME_STATE_DTO_H__

#include <vector>

class ClientGameStateDTO {
public:
    ClientGameStateDTO() = delete;
    explicit ClientGameStateDTO(float width, float height);
    ~ClientGameStateDTO() = default;

    float width;
    float height;

    int active_client_id;
    int active_entity_id;
    
    float wind_speed; // positivo o negativo
    float remaining_game_time;
    float remaining_turn_time;
    
    std::vector<WormDTO> worms;
    std::vector<BeamDto> beams;
    std::vector<BulletDto> bullets;
    std::vector<WorldEventDto> events;

    // const float scale;
    // const float xoffset;
    // const float yoffset;
};


#endif

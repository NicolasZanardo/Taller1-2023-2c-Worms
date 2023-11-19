#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include <map>
#include <string>
#include <memory>

#include "game_display.h"
#include "game_worm_entity.h"
#include "client_game_state_dto.h"

class ClientGameState {
    GameDisplay& display;
    int game_remaining_time;
    int turn_remaining_time;
    float width;
    float height;

    // std::unique_ptr<ClientGameStateDTO> game_state_dto;
    std::map<int, std::shared_ptr<WormEntity>> worms;

    public:
    ClientGameState() = delete;
    explicit ClientGameState(GameDisplay& display);
    ~ClientGameState() = default;

    void load(std::shared_ptr<ClientGameStateDTO> game_state_dto);
    void update(std::shared_ptr<ClientGameStateDTO> game_state_dto);
    
};

#endif // __PLAYER_STATE_H__

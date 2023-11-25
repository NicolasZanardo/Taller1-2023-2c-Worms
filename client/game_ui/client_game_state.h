#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include <map>
#include <string>
#include <memory>

#include "game_display.h"
#include "game_ui_text.h"
#include "game_display/worm/game_worm_entity.h"
#include "client_game_state_dto.h"

class ClientGameState {
    GameDisplay& display;
    int game_remaining_time;
    int turn_remaining_time;
    float width;
    float height;
    GameUiText* turnDisplay;


    // std::unique_ptr<ClientGameStateDTO> game_state_dto;
    std::map<int, std::shared_ptr<WormEntity>> worms;
    std::map<int, std::shared_ptr<WormEntity>> death_worms;

    void transfer_death_worms(std::vector<WormDto> updated_worms);

    public:
    int my_client_id;
    explicit ClientGameState(GameDisplay& display);
    ClientGameState() = delete;
    ~ClientGameState() = default;

    void load(const std::shared_ptr<ClientGameStateDTO>& game_state_dto);
    void update(const std::shared_ptr<ClientGameStateDTO>& game_state_dto);
    
};

#endif // __PLAYER_STATE_H__

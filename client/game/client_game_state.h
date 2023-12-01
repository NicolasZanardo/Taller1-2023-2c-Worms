#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include <map>
#include <string>
#include <memory>

#include "game_display.h"
#include "game_worm_entity.h"
#include "game_text_display.h"
#include "client_game_state_dto.h"
#include "projectiles/game_projectile_entity.h"
#include "game_timer.h"

class ClientGameState {
    GameDisplay& display;
    float width;
    float height;
    GameTextDisplay* turnDisplay;
    GameTimer timer;

    // std::unique_ptr<ClientGameStateDTO> game_state_dto;
    std::map<int, std::shared_ptr<WormEntity>> worms;
    std::map<int, std::shared_ptr<WormEntity>> death_worms;

    std::map<int, std::shared_ptr<ProjectileEntity>> projectiles;

    void transfer_death_worms(std::vector<WormDto> updated_worms);
    void destroy_old_projectiles(std::vector<ProjectileDto> updated_projectiles);
    void focus_camera_on(int entity_id);

    public:
    int my_client_id;
    explicit ClientGameState(GameDisplay& display);
    ClientGameState() = delete;
    ~ClientGameState() = default;

    void load(const std::shared_ptr<ClientGameStateDTO>& game_state_dto);
    void update(const std::shared_ptr<ClientGameStateDTO>& game_state_dto);
    
};

#endif // __PLAYER_STATE_H__

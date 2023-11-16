#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include <map>
#include <string>

#include "animation.h"
#include "drawable_integer.h"
#include "icon.h"
#include "non_animation.h"
#include "sprites_manager.h"
#include "client_game_state_dto.h"
#include "worm_state.h"
#include "beam_state.h"

class ClientGameState {
public:
    ClientGameState() = delete;
    explicit ClientGameState(SpritesManager& sprites_manager);
    ~ClientGameState() = default;

    void load();
    void update(std::unique_ptr<ClientGameStateDTO> game_state_dto, float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    SpritesManager* sprites_manager;
    // std::map<std::string, WormState> worms;  // The key is the id.
    // WormState worm_state;

    int game_remaining_time;
    int turn_remaining_time;

    // std::unique_ptr<ClientGameStateDTO> game_state_dto;
    std::map<int, WormState> worms_state;
    std::vector<BeamState> beams_state;

    // Animation an;
    // bool facingLeft;
    // bool moving;
    // int x;
    // int y;

    // std::map<>
};

#endif // __PLAYER_STATE_H__

#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include "client_game_state_dto.h"
#include "animation.h"
#include "sprites_manager.h"

#include "wormDto.h"

class WormState {
public:
    WormState() = delete;
    explicit WormState(SpritesManager& sprites_manager);
    ~WormState() = default;

    WormState(WormState&& other);
    WormState& operator=(WormState&& other);

    void update(WormDTO& update_data, float dt);
    void render();
    // void moveRigth();
    // void moveLeft();
    // void stopMoving();

private:
    // Animation an;
    MovementState state;
    bool facingLeft;
    // bool moving;
    int x;
    int y;

    Animation* current_animation;

    std::map<MovementState, Animation> animations;
};

#endif  // __WORM_STATE_H__

#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include <unordered_map>
#include "client_game_state_dto.h"
#include "animation.h"
#include "sprites_manager.h"

class WormState {
public:
    WormState() = delete;
    explicit WormState(SpritesManager& sprites_manager);
    ~WormState() = default;

    WormState(WormState&& other) noexcept ;
    WormState& operator=(WormState&& other) noexcept ;

    void update(WormDto& updated_data, float dt);
    void render();

    int x;
    int y;

private:
    // Animation an;
    MovementStateDto state;
    bool facingLeft;
    // bool moving;


    std::unordered_map<MovementStateDto, std::shared_ptr<Animation>> animations;
    std::shared_ptr<Animation> current_animation;
};

#endif  // __WORM_STATE_H__

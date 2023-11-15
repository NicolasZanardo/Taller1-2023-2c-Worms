#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include <map>
#include <string>

#include "animation.h"
#include "drawable_integer.h"
#include "icon.h"
#include "non_animation.h"
#include "sprites_manager.h"

#include "worm_state.h"

class ClientGameState {
public:
    ClientGameState() = delete;
    explicit ClientGameState(SpritesManager& sprites_manager);
    ~ClientGameState() = default;

    void load();
    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    SpritesManager* sprites_manager;
    std::map<std::string, WormState> worms;  // The key is the id.
    WormState worm_state;


    // Animation an;
    // bool facingLeft;
    // bool moving;
    // int x;
    // int y;
};

#endif // __PLAYER_STATE_H__

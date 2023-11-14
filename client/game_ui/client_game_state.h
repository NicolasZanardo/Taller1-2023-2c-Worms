#ifndef __CLIENT_STATE_H__
#define __CLIENT_STATE_H__

#include "animation.h"
#include "drawable_integer.h"
#include "icon.h"
#include "non_animation.h"
#include "sprites_manager.h"

class ClientGameState {
public:
    explicit ClientGameState(SpritesManager& sprites_manager);
    ~ClientGameState() = default;

    void update(float dt);
    void render();
    void moveRigth();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif // __PLAYER_STATE_H__

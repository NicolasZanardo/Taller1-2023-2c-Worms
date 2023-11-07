#ifndef __PLAYER_STATE_H__
#define __PLAYER_STATE_H__

#include "animation.h"
#include "sprite.h"

class PlayerState {
public:
    PlayerState(Sprite& sprite);
    ~PlayerState() = default;

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

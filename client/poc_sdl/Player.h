#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Animation.h"
#include "./sprite.h"

class Player {
public:
    Player(Sprite& sprite);
    ~Player() = default;

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

#endif // __PLAYER_H__

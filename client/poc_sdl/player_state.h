#ifndef __PLAYER_STATE_H__
#define __PLAYER_STATE_H__

#include "animation.h"
#include "drawable_integer.h"
#include "icon.h"
#include "non_animation.h"
#include "sprites_manager.h"


class PlayerState {
public:
    explicit PlayerState(SpritesManager& sprites_manager);
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

#ifndef __WORM_STATE_H__
#define __WORM_STATE_H__

#include "animation.h"
#include "sprites_manager.h"

class WormState {
public:
    WormState() = delete;
    explicit WormState(SpritesManager& sprites_manager);
    ~WormState() = default;

    WormState(WormState&& other);
    WormState& operator=(WormState&& other);

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

#endif  // __WORM_STATE_H__

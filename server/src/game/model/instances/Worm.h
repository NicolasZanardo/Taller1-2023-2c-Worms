#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include "Instance.h"
#include "../../../../../common_base/Game/wormDto.h"
#include "box2d/box2d.h"

class InstancesManager;

class Worm: public Instance {
private:
    friend class InstancesManager;
    b2Body* body;


    // Movement
    const float speed = 0.2f;
    const float forwardJumpHeight = 1.0f;
    const float forwardJumpReach = 0.5f;
    const float backwardsJumpHeight = 1.2f;
    const float backwardsJumpReach = 0.2f;

    bool isJumping = false;
    bool isFacingRight = true;
    short getFacingDirectionSign() const;


    Worm(size_t id);
public:
    int health = 100;


    WormDto toWormDto(size_t clientId);

    void startMovingRight();
    void startMovingLeft();
    void stopMoving();
    void jumpForward();
    void jumpBackwards();
    void onUpdatePhysics();
};

#endif

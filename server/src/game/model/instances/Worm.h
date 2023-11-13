#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include "Instance.h"
#include "../../../../../common_base/Game/wormDto.h"
#include "box2d/box2d.h"

class InstancesManager;

class Worm : public Instance {
private:
    enum class State : uint8_t {
        idle = 0x00,
        walking = 0x01,
        jumping = 0x02,
        shooting = 0x03,
        dead = 0x04,
        falling = 0x05,
        damaged = 0x06
    };
    State state;
    friend class InstancesManager;

    b2Body *body;


    // Movement
    const float speed = 0.2f;
    const float forwardJumpHeight = 1.0f;
    const float forwardJumpReach = 0.5f;
    const float backwardsJumpHeight = 1.2f;
    const float backwardsJumpReach = 0.2f;
    bool isJumping = false;
    bool isFacingRight = true;

    short getFacingDirectionSign() const;
    WormDto::State stateToDto() const;


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

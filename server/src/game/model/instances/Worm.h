#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include <memory>
#include "Instance.h"
#include "../../../../../common_base/Game/wormDto.h"
#include "../WormMovement.h"

class InstancesManager;

class Worm : public Instance {
private:
    friend class InstancesManager;
    explicit Worm(size_t id);

public:
    std::shared_ptr<WormMovement> movement;
    int health = 100;

    WormDto toWormDto(size_t clientId);

    void startMovingRight();

    void startMovingLeft();

    void stopMoving();

    void jumpForward();

    void jumpBackwards();

    // void on_update_physics();
};

#endif

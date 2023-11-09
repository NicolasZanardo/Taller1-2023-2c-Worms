#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include "Instance.h"
#include "../../../../common_base/Game/wormDto.h"
#include <box2d/box2d.h>

class InstancesManager;

class Worm: public Instance {
private:
    friend class InstancesManager;
    b2Body* body;
    Worm(size_t id);
public:
    int health = 100;

    WormDto toWormDto(int clientId);
};

#endif

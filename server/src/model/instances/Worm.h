#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include "Instance.h"
#include <box2d/box2d.h>

class Worm: public Instance {
private:
    b2Body* body;
public:
    int health = 100;
    Worm(size_t id, b2Body* body); // TODO Encapsulate body in a PhysicsComponent
};

#endif

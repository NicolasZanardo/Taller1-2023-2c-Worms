#ifndef SERVER_WORM_H
#define SERVER_WORM_H

#include "Entity.h"
#include <box2d/box2d.h>

class Worm: public Entity {
private:
    b2Body* body;
public:
    int health = 100;
    Worm(size_t id, b2Body* body); // TODO Encapsulate body in a PhysicsComponent
};

#endif

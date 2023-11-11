#ifndef TP_WORMS_PHYSICSCOLLISIONLISTENER_H
#define TP_WORMS_PHYSICSCOLLISIONLISTENER_H

#include "box2d/box2d.h"

class PhysicsCollisionListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override;
};

#endif

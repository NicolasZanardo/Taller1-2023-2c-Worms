#ifndef TP_WORMS_PHYSICSCOLLISIONLISTENER_H
#define TP_WORMS_PHYSICSCOLLISIONLISTENER_H

#include <Box2D/Box2D.h>

class PhysicsCollisionListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override;
};

#endif

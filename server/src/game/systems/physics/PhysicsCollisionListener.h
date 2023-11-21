#ifndef TP_WORMS_PHYSICSCOLLISIONLISTENER_H
#define TP_WORMS_PHYSICSCOLLISIONLISTENER_H

#include "box2d/box2d.h"
#include "../../model/worm/Worm.h"

class PhysicsCollisionListener : public b2ContactListener {
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

private:
    // Queries
    Worm* get_worm_from_fixture(b2Fixture* fixtureA, b2Fixture* fixtureB);

    // Begin conctact events
    void on_worm_began_contact_with_ground(b2Fixture* fixtureA, b2Fixture* fixtureB);

    // End contact events
    void on_worm_ended_contact_with_ground(b2Fixture* fixtureA, b2Fixture* fixtureB);
};

#endif


#include "BWormWithGround.h"
#include "../../../model/worm/Worm.h"
#include <iostream>

bool BWormWithGround::try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) {
    bool isFootSensorA = fixtureA->IsSensor();
    bool isFootSensorB = fixtureB->IsSensor();

    if (isFootSensorA || isFootSensorB) {
        Worm* worm = query.get_object_from_fixture<Worm>(fixtureA, fixtureB);
        if (worm && worm->body) {
            worm->body->ground_contact_count++;
            worm->body->is_on_ground = (worm->body->ground_contact_count > 0);
            return true;
        }
    }
    return false;
}

BWormWithGround::BWormWithGround(b2World &world) : CollisionEvent(world) {}

#include "PhysicsCollisionListener.h"
#include "../model/instances/Instance.h"
#include "../model/instances/Worm.h"
#include <iostream>

void PhysicsCollisionListener::BeginContact(b2Contact *contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    on_worm_began_contact_with_ground(fixtureA, fixtureB);
}

void PhysicsCollisionListener::EndContact(b2Contact *contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    on_worm_ended_contact_with_ground(fixtureA, fixtureB);

}

void PhysicsCollisionListener::on_worm_began_contact_with_ground(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    bool isFootSensorA = fixtureA->IsSensor();
    bool isFootSensorB = fixtureB->IsSensor();

    if (isFootSensorA || isFootSensorB) {
        Worm* worm = get_worm_from_fixture(fixtureA, fixtureB);
        if (worm && worm->movement) {
            worm->movement->ground_contact_count++;
            worm->movement->is_on_ground = (worm->movement->ground_contact_count > 0);
        }
    }
}

void PhysicsCollisionListener::on_worm_ended_contact_with_ground(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    bool isFootSensorA = fixtureA->IsSensor();
    bool isFootSensorB = fixtureB->IsSensor();

    if (isFootSensorA || isFootSensorB) {
        Worm* worm = get_worm_from_fixture(fixtureA, fixtureB);
        if (worm && worm->movement) {
            worm->movement->ground_contact_count--;
            worm->movement->is_on_ground = (worm->movement->ground_contact_count > 0);
        }
    }
}


Worm* PhysicsCollisionListener::get_worm_from_fixture(b2Fixture* fixtureA, b2Fixture* fixtureB) {
    bool isFootSensorA = fixtureA->IsSensor();
    bool isFootSensorB = fixtureB->IsSensor();

    if (isFootSensorA || isFootSensorB) {
        uintptr_t wormPtr = isFootSensorA ? fixtureA->GetUserData().pointer : fixtureB->GetUserData().pointer;
        return reinterpret_cast<Worm*>(wormPtr);
    }

    return nullptr;
}


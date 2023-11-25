#include "PhysicsCollisionListener.h"
#include "begin_contact_events/BWormWithGround.h"
#include "begin_contact_events/BProjectileWithAny.h"
#include "end_contact_events/EWormWithGround.h"
#include <iostream>


// TODO Should maybe have a map with a pair of tags pointing to a CollisionEventResolution function
// Instead of quering by trying to cast and returning true if resolved
/*
 *  A successful resolution breaks the BeginContact method
 *  For now, the events  represent a (1 to 1 contact) or (1 to Any),
 *  so if a (1 to 1) or (1 to any) contact is resolved
 *  it means there is no other possible combination left to analyze.
 *  (1 to Any) should handle all cases for Any in order for the rest of events to be excluded
 */
void PhysicsCollisionListener::BeginContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    for (auto &event: beginning_collisions) {
         if (event->try_resolve(fixtureA, fixtureB))
             return;
    }

}

void PhysicsCollisionListener::EndContact(b2Contact *contact) {
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    for (auto &event: ending_collisions) {
        if (event->try_resolve(fixtureA, fixtureB))
            return;
    }
}

/*
 * Set the events with priority in mind
 */
PhysicsCollisionListener::PhysicsCollisionListener(b2World &world) : world(world), beginning_collisions(), ending_collisions(){
    _init_beginning_collision_events();
    _init_ending_collision_events();
}

void PhysicsCollisionListener::_init_beginning_collision_events() {
    beginning_collisions.emplace_back(std::make_unique<BWormWithGround>(world));
    beginning_collisions.emplace_back(std::make_unique<BProjectileWithAny>(world));
}

void PhysicsCollisionListener::_init_ending_collision_events() {
    ending_collisions.emplace_back(std::make_unique<EWormWithGround>(world));
}




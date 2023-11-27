#include "PhysicsCollisionListener.h"
#include "begin_collision_events/BWaterWProjectile.h"
#include "end_collision_events/EWormFootSensorWGround.h"
#include "../../core/CollideableTags.h"
#include "begin_collision_events/BWaterWWorm.h"
#include "begin_collision_events/BWormFootSensorWGround.h"
#include "begin_collision_events/BProjectileWAny.h"
#include <iostream>

void PhysicsCollisionListener::BeginContact(b2Contact *contact) {

    auto collidable_a = reinterpret_cast<Collidable *>(contact->GetFixtureA()->GetUserData().pointer);
    auto collidable_b = reinterpret_cast<Collidable *>(contact->GetFixtureB()->GetUserData().pointer);

    if (!collidable_a || !collidable_b)
        return;

    auto tree = beginning_hit_map.find(std::make_pair(collidable_a->tag, collidable_b->tag));
    if (tree != beginning_hit_map.end()) {
        auto resolver = tree->second;
        if (resolver)
            resolver(collidable_a, collidable_b, contact);
    }
}

void PhysicsCollisionListener::EndContact(b2Contact *contact) {
    auto collidable_a = reinterpret_cast<Collidable *>(contact->GetFixtureA()->GetUserData().pointer);
    auto collidable_b = reinterpret_cast<Collidable *>(contact->GetFixtureB()->GetUserData().pointer);

    if (!collidable_a || !collidable_b)
        return;

    auto tree = ending_hit_map.find(std::make_pair(collidable_a->tag, collidable_b->tag));
    if (tree != ending_hit_map.end()) {
        auto resolver = tree->second;
        if (resolver)
            resolver(collidable_a, collidable_b, contact);
    }

}

PhysicsCollisionListener::PhysicsCollisionListener() : beginning_hit_map(), ending_hit_map() {
    _init_beginning_collisions_hit_map();
    _init_ending_collisions_hit_map();
}

void PhysicsCollisionListener::_init_beginning_collisions_hit_map() {

    // Worm foot sensor

    beginning_hit_map.insert(
        std::make_pair(std::make_pair(WORM_FOOT_SENSOR_TAG, GROUND_TAG), &BWormFootSensorWGround::resolve)
    );
    beginning_hit_map.insert(
        std::make_pair(std::make_pair(GROUND_TAG, WORM_FOOT_SENSOR_TAG), &BWormFootSensorWGround::resolve_inverse)
    );

    // Projectile

    beginning_hit_map.insert(
        std::make_pair(std::make_pair(PROJECTILE_TAG, GROUND_TAG), &BProjectileWAny::resolve)
    );
    beginning_hit_map.insert(
        std::make_pair(std::make_pair(GROUND_TAG, PROJECTILE_TAG), &BProjectileWAny::resolve_inverse)
    );

    beginning_hit_map.insert(
        std::make_pair(std::make_pair(PROJECTILE_TAG, WORM_TAG), &BProjectileWAny::resolve)
    );
    beginning_hit_map.insert(
        std::make_pair(std::make_pair(WORM_TAG, PROJECTILE_TAG), &BProjectileWAny::resolve_inverse)
    );


    // Water

    beginning_hit_map.insert(
        std::make_pair(std::make_pair(WATER_TAG, PROJECTILE_TAG), &BWaterWProjectile::resolve)
    );
    beginning_hit_map.insert(
        std::make_pair(std::make_pair(PROJECTILE_TAG, WATER_TAG), &BWaterWProjectile::resolve_inverse)
    );

    beginning_hit_map.insert(
        std::make_pair(std::make_pair(WATER_TAG, WORM_TAG), &BWaterWWorm::resolve)
    );
    beginning_hit_map.insert(
        std::make_pair(std::make_pair(WORM_TAG, WATER_TAG), &BWaterWWorm::resolve_inverse)
    );

}

void PhysicsCollisionListener::_init_ending_collisions_hit_map() {
    // Worm foot sensor
    ending_hit_map.insert(
        std::make_pair(std::make_pair(WORM_FOOT_SENSOR_TAG, GROUND_TAG), &EWormFootSensorWGround::resolve)
    );
    ending_hit_map.insert(
        std::make_pair(std::make_pair(GROUND_TAG, WORM_FOOT_SENSOR_TAG), &EWormFootSensorWGround::resolve_inverse)
    );


}

#ifndef TP_WORMS_PHYSICSCOLLISIONLISTENER_H
#define TP_WORMS_PHYSICSCOLLISIONLISTENER_H

#include "box2d/box2d.h"
#include "../../model/worm/Worm.h"
#include "../../model/projectiles/Projectile.h"
#include "UserDataQuery.h"
#include "CollisionEvent.h"

class PhysicsCollisionListener : public b2ContactListener {
    b2World& world;
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

    std::vector<std::unique_ptr<CollisionEvent>>  beginning_collisions;
    std::vector<std::unique_ptr<CollisionEvent>>  ending_collisions;

    void _init_beginning_collision_events();
    void _init_ending_collision_events();
public:
    explicit PhysicsCollisionListener(b2World& world);
};

#endif

#ifndef TP_WORMS_BPROJECTILEWITHANY_H
#define TP_WORMS_BPROJECTILEWITHANY_H

#include "../CollisionEvent.h"
#include "../raycast_callbacks/ProjectileExplosionQueryCallback.h"

class BProjectileWithAny: public CollisionEvent {
    const float explosion_power = 20;

    void apply_blast_impulse(b2Body* body, b2Vec2 blast_center, b2Vec2 apply_point, float distance);
public:
    explicit BProjectileWithAny(b2World& world);
    bool try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) override;
};


#endif //TP_WORMS_BPROJECTILEWITHANY_H

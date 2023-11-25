#ifndef TP_WORMS_BPROJECTILEWITHANY_H
#define TP_WORMS_BPROJECTILEWITHANY_H

#include <unordered_set>
#include "../CollisionEvent.h"
#include "../raycast_callbacks/OnProjectileExplosionRayCast.h"

class BProjectileWithAny: public CollisionEvent {
    OnProjectileExplosionRayCast onExplosionRayCast;
    const int num_rays = 32;
    const float blastPower = 60;
    std::unordered_set<Worm*> unique_worms;

    void apply_blast_impulse(b2Body* body, b2Vec2 blast_center, b2Vec2 apply_point, float blast_power);
public:
    explicit BProjectileWithAny(b2World& world);
    bool try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) override;
};


#endif //TP_WORMS_BPROJECTILEWITHANY_H

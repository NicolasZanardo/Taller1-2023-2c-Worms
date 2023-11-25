#ifndef TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H
#define TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H

#include <box2d/box2d.h>
#include <algorithm>
#include "../fixture_queries/FixtureQueries.h"
#include "../../../model/worm/Worm.h"
#include <list>

class WormHitInfo {
public:
    Worm* worm;
    b2Vec2 hit_point;
    float fraction;

    WormHitInfo(Worm* worm, const b2Vec2& hit_point, const float fraction) : worm(worm), hit_point(hit_point), fraction(fraction) {}
};

class OnProjectileExplosionRayCast: public b2RayCastCallback {
    FixtureQueries &query;
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;
public:
    std::vector< WormHitInfo> worms_hit;
    OnProjectileExplosionRayCast(FixtureQueries& query);
    void reset();
};


#endif //TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H

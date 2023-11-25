#ifndef TP_WORMS_ONPROJECTILEEXPLOSIONQUERY_H
#define TP_WORMS_ONPROJECTILEEXPLOSIONQUERY_H

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

class OnProjectileExplosionQuery: public b2QueryCallback {
    FixtureQueries &query;
    bool ReportFixture(b2Fixture* fixture) override;
public:
    std::vector< WormHitInfo> worms_hit;
    OnProjectileExplosionQuery(FixtureQueries& query);
    void reset();
};


#endif //TP_WORMS_ONPROJECTILEEXPLOSIONQUERY_H

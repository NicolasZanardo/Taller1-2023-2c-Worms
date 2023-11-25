#ifndef TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H
#define TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H

#include <box2d/box2d.h>
#include "../fixture_queries/FixtureQueries.h"
#include "../../../model/worm/Worm.h"

class OnProjectileExplosionRayCast: public b2RayCastCallback {
    FixtureQueries &query;
    float ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction) override;
public:
    Worm* worm;
    b2Vec2 ray_cast_hit_point;
    OnProjectileExplosionRayCast(FixtureQueries& query);
};


#endif //TP_WORMS_ONPROJECTILEEXPLOSIONRAYCAST_H

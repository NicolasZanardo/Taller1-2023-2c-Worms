#include "OnProjectileExplosionRayCast.h"

float OnProjectileExplosionRayCast::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal,
                                                  float fraction) {
    auto hit_worm = query.get_user_data_as_type<Worm>(fixture);
    if (hit_worm) {
        worm = hit_worm;
        ray_cast_hit_point = point;
        return 1;
    }

    // Else collided with ground
    return fraction;
}

OnProjectileExplosionRayCast::OnProjectileExplosionRayCast(FixtureQueries &query): query(query), ray_cast_hit_point(0,0){}

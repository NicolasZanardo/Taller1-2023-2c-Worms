#include "OnProjectileExplosionRayCast.h"

float OnProjectileExplosionRayCast::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal,
                                                  float fraction) {
    auto hit_worm = query.get_user_data_as_type<Worm>(fixture);
    if (hit_worm) {
        worms_hit.emplace_back(hit_worm, point, fraction);
        return 1;
    }
    // Else collided with ground
    // Removed every WormHit that has fraction greater than the fraction to the ground
    worms_hit.erase(std::remove_if(worms_hit.begin(), worms_hit.end(), [fraction](const WormHitInfo& worm_hit) {
        return worm_hit.fraction > fraction;
    }), worms_hit.end());

    return fraction; // clip ray to the ground
}

OnProjectileExplosionRayCast::OnProjectileExplosionRayCast(FixtureQueries &query): query(query), worms_hit(){}

void OnProjectileExplosionRayCast::reset() {
    void reset();
}

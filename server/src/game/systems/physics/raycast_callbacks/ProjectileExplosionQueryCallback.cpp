#include "ProjectileExplosionQueryCallback.h"

bool ProjectileExplosionQueryCallback::ReportFixture(b2Fixture* fixture) {
    auto hit_worm = query.get_user_data_as_type<Worm>(fixture);
    if (hit_worm) {
        found_worms_map[hit_worm->Id()] = hit_worm;
    }

    return true;
}

ProjectileExplosionQueryCallback::ProjectileExplosionQueryCallback(UserDataQuery &query): query(query), found_worms_map() {}


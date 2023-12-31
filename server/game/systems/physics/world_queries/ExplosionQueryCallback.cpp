#include "ExplosionQueryCallback.h"

bool ExplosionQueryCallback::ReportFixture(b2Fixture* fixture) {
    auto hit_worm = UserDataQuery::get_user_data_as_type<Worm>(fixture);
    if (hit_worm) {
        // If worm has multiple fixtures we just need that worm one time
        found_worms_map[hit_worm->Id()] = hit_worm;
    }

    return true;
}

ExplosionQueryCallback::ExplosionQueryCallback(): found_worms_map() {}


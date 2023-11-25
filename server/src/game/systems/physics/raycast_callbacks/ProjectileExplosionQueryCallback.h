#ifndef TP_WORMS_PROJECTILEEXPLOSIONQUERYCALLBACK_H
#define TP_WORMS_PROJECTILEEXPLOSIONQUERYCALLBACK_H

#include <box2d/box2d.h>
#include <algorithm>
#include "../UserDataQuery.h"
#include "../../../model/worm/Worm.h"
#include <map>

class ProjectileExplosionQueryCallback: public b2QueryCallback {
    UserDataQuery &query;
    bool ReportFixture(b2Fixture* fixture) override;
public:
    std::map<size_t , Worm*> found_worms_map;

    explicit ProjectileExplosionQueryCallback(UserDataQuery& query);
};


#endif

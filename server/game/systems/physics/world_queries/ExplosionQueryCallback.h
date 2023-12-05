#ifndef TP_WORMS_EXPLOSIONQUERYCALLBACK_H
#define TP_WORMS_EXPLOSIONQUERYCALLBACK_H

#include <box2d/box2d.h>
#include <algorithm>
#include "UserDataQuery.h"
#include "Worm.h"
#include <map>

class ExplosionQueryCallback: public b2QueryCallback {
    bool ReportFixture(b2Fixture* fixture) override;
public:
    std::map<size_t , Worm*> found_worms_map;

    explicit ExplosionQueryCallback();
};


#endif

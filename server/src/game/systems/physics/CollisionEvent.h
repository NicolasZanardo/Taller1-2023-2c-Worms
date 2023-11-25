#ifndef TP_WORMS_COLLISIONEVENT_H
#define TP_WORMS_COLLISIONEVENT_H

#include <box2d/box2d.h>
#include "fixture_queries/FixtureQueries.h"

class CollisionEvent {
protected:
    b2World &world;
    FixtureQueries query;
public:
    explicit CollisionEvent(b2World &world): world(world), query() {}
    virtual bool try_resolve(b2Fixture* fixtureA, b2Fixture* fixtureB) = 0;
    virtual ~CollisionEvent() = default;
};

#endif //TP_WORMS_COLLISIONEVENT_H

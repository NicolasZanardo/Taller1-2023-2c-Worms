#ifndef TP_WORMS_EWORMWITHGROUND_H
#define TP_WORMS_EWORMWITHGROUND_H

#include "../CollisionEvent.h"

class EWormWithGround: public CollisionEvent {
public:
    explicit EWormWithGround(b2World& world);
    bool try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) override;
};


#endif //TP_WORMS_EWORMWITHGROUND_H

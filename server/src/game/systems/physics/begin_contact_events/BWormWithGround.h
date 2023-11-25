#ifndef TP_WORMS_BWORMWITHGROUND_H
#define TP_WORMS_BWORMWITHGROUND_H


#include "../CollisionEvent.h"

class BWormWithGround: public CollisionEvent {
public:
    explicit BWormWithGround(b2World& world);
    bool try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) override;
};


#endif //TP_WORMS_BWORMWITHGROUND_H

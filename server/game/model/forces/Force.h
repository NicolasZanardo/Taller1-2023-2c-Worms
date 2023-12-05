#ifndef TP_WORMS_FORCE_H
#define TP_WORMS_FORCE_H

#include <box2d/box2d.h>

class Force {
protected:
    b2World& world;
public:
    explicit Force(b2World& world) : world(world) {}

    Force(const Force&) = delete;
    Force& operator=(const Force&) = delete;
    Force(Force&& other) = delete;
    Force& operator=(Force&& other) = delete;

    virtual void apply(b2Body* body) = 0;

    virtual ~Force() = default;

};


#endif //TP_WORMS_FORCE_H

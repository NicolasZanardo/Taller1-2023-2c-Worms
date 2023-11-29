#ifndef TP_WORMS_BODY_H
#define TP_WORMS_BODY_H

#include <box2d/box2d.h>
#include <memory>
#include "Force.h"

class Body {
protected:
    b2World &world;
    b2Body *body;
    bool is_facing_right;
public:

    Body(b2World &world, b2Body *body, bool is_facing_right);

    b2Body *B2Body();

    float X() const;

    float Y() const;

    float Angle() const;

    void receive(Force &force);

    bool is_moving_faster_than(const std::shared_ptr<Body> &other);

    bool facing_right() const;

    ~Body();
};


#endif //TP_WORMS_BODY_H

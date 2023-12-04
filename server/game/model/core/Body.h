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
    Body(Body&& other) noexcept;

    b2Body *B2Body();

    float X() const;

    float Y() const;

    bool is_still() const;

    float AngleInDeg() const;

    virtual void receive(Force &force);

    bool is_moving_faster_than(const std::shared_ptr<Body> &other);

    ~Body();

    bool facing_right() const;
};


#endif //TP_WORMS_BODY_H

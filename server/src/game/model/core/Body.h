#ifndef TP_WORMS_BODY_H
#define TP_WORMS_BODY_H

#include <box2d/box2d.h>
#include "../forces/Force.h"

class Body {
protected:
    b2World &world;
    b2Body *body;
public:

    Body(b2World &world, b2Body *body);

    b2Body *B2Body();

    float X() const;

    float Y() const;

    void receive(Force &force);

    ~Body();
};


#endif //TP_WORMS_BODY_H

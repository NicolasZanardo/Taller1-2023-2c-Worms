#ifndef TP_WORMS_PROJECTILEBODY_H
#define TP_WORMS_PROJECTILEBODY_H

#include <box2d/box2d.h>
#include "../core/Body.h"

class ProjectileBody: public Body {
public:
    ProjectileBody(b2World& world, b2Body* body);

    ~ProjectileBody() = default;
};


#endif

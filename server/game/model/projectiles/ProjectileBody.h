#ifndef TP_WORMS_PROJECTILEBODY_H
#define TP_WORMS_PROJECTILEBODY_H

#include <box2d/box2d.h>
#include "Body.h"

class ProjectileBody: public Body {
    bool spawned_facing_right;
    bool is_on_water;
public:
    ProjectileBody(b2World& world, b2Body* body, bool is_facing_right);

    void sink();

    void on_update();

    bool did_spawned_facing_right() const;

    ~ProjectileBody() = default;
};


#endif

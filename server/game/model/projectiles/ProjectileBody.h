#ifndef TP_WORMS_PROJECTILEBODY_H
#define TP_WORMS_PROJECTILEBODY_H

#include <box2d/box2d.h>
#include <memory>
#include "Body.h"
#include "RotationStrategy.h"

class ProjectileBody: public Body {
    bool spawned_facing_right;
    bool is_on_water;
    std::unique_ptr<RotationStrategy> rotation_strategy;

public:
    ProjectileBody(b2World& world, b2Body* body, bool is_facing_right, std::unique_ptr<RotationStrategy> rotation_strategy);

    void sink();

    void on_update();

    bool did_spawned_facing_right() const;

    ~ProjectileBody() = default;
};


#endif

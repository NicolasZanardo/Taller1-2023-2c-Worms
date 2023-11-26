#ifndef TP_WORMS_BUOYANCYFORCE_H
#define TP_WORMS_BUOYANCYFORCE_H

#include "Force.h"

class BuoyancyForce: public Force {
public:
    explicit BuoyancyForce(b2World& world);
    void apply(b2Body *body) override;
};


#endif //TP_WORMS_BUOYANCYFORCE_H

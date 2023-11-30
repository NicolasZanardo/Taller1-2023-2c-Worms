#ifndef TP_WORMS_EXPLOSIONFORCE_H
#define TP_WORMS_EXPLOSIONFORCE_H

#include "Force.h"

class ExplosionForce: public Force {
    constexpr static const float EXPLOSION_POWER = 120;
    b2Vec2 explosion_point;
public:
    explicit ExplosionForce(b2World& world, b2Vec2 explosion_point);
    void apply(b2Body *body) override;
};


#endif //TP_WORMS_EXPLOSIONFORCE_H
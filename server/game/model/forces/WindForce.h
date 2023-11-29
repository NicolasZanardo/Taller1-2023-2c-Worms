#ifndef TP_WORMS_WINDFORCE_H
#define TP_WORMS_WINDFORCE_H

#include "Force.h"

class WindForce : public Force {
    float wind_speed;

public:
    WindForce(b2World &world, float wind_speed);

    void apply(b2Body *body) override;
    void on_wind_change(float wind_speed);
};

#endif //TP_WORMS_WINDFORCE_H

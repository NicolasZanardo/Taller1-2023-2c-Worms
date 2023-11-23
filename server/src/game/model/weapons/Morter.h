#ifndef TP_WORMS_MORTER_H
#define TP_WORMS_MORTER_H

#include "Weapon.h"

class Morter: public Weapon {
public:
    explicit Morter(int ammo_left, Damage damage);

    void start_shooting(float from_x, float from_y) override;
    void end_shooting(float from_x, float from_y) override;
};

#endif //TP_WORMS_MORTER_H

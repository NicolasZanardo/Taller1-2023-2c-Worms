#ifndef TP_WORMS_BAZOOKA_H
#define TP_WORMS_BAZOOKA_H

#include "Weapon.h"

class Bazooka: public Weapon {
public:
    explicit Bazooka(int ammo_left, float damage, float explosion_radius);

    void start_shooting(float from_x, float from_y) override;
    void end_shooting(float from_x, float from_y) override;
};


#endif //TP_WORMS_BAZOOKA_H

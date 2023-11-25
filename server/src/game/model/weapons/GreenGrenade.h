#ifndef TP_WORMS_GREEN_GRANADE_H
#define TP_WORMS_GREEN_GRANADE_H


#include "Weapon.h"

class GreenGrenade : public Weapon {
public:
    explicit GreenGrenade(int ammo_left, float damage, float explosion_radius);

    void start_shooting(float from_x, float from_y) override;

    void end_shooting(float from_x, float from_y) override;
};


#endif //TP_WORMS_GREEN_GRANADE_H

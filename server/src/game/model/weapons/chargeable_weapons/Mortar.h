#ifndef TP_WORMS_MORTAR_H
#define TP_WORMS_MORTAR_H

#include "Weapon.h"

class Mortar: public Weapon {
public:
    explicit Mortar(int ammo_left, float damage, float explosion_radius);

    void start_shooting(float from_x, float from_y, char facing_direction) override;
    void end_shooting(float from_x, float from_y, char facing_direction) override;
    bool change_projectile_count_down(ProjectileCountDown time) override;
};

#endif //TP_WORMS_MORTAR_H

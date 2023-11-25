#ifndef TP_WORMS_MORTAR_H
#define TP_WORMS_MORTAR_H

#include "Weapon.h"

class Mortar: public Weapon {
public:
    explicit Mortar(size_t owner_id, int ammo_left, float damage, float explosion_radius);

    void start_shooting(float from_x, float from_y, char facing_direction) override;
    void end_shooting(float from_x, float from_y, char facing_direction) override;
};

#endif //TP_WORMS_MORTAR_H

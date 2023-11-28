#ifndef TP_WORMS_BAZOOKA_H
#define TP_WORMS_BAZOOKA_H

#include "ChargeableWeapon.h"

class Bazooka: public ChargeableWeapon {
    const float max_shoot_power;
public:
    explicit Bazooka(
        int ammo_left,
        float damage,
        float explosion_radius,
        float max_shoot_power
        );

    std::unique_ptr<CShot> shoot(float charged_power, float from_x, float from_y, char facing_sign) override;
    bool change_projectile_count_down(ProjectileCountDown time) override;
};


#endif //TP_WORMS_BAZOOKA_H

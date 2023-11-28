#ifndef TP_WORMS_INSTANT_WEAPON_EXAMPLE_H
#define TP_WORMS_INSTANT_WEAPON_EXAMPLE_H

#include "InstantShotWeapon.h"

class InstantWeaponExample : public InstantShotWeapon {
    int projectile_countdown;
    const int default_projectile_countdown;
    const float shoot_power;
public:
    explicit InstantWeaponExample(
        int ammo_left,
        float max_damage,
        float explosion_radius,
        int default_count_down_time,
        float shoot_power
    );

    bool change_projectile_count_down(ProjectileCountDown time) override;
    void on_turn_ended() override;
    std::unique_ptr<CShot> shoot(float from_x, float from_y, char facing_sign) override;
};

#endif

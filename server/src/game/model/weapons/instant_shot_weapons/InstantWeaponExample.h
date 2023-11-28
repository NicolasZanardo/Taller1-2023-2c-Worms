#ifndef TP_WORMS_GREEN_GRANADE_H
#define TP_WORMS_GREEN_GRANADE_H

#include "InstantShotWeapon.h"

class GreenGrenade : public InstantShotWeapon {
    int projectile_countdown;
    const int default_projectile_countdown;
    const float shoot_power;
public:
    explicit GreenGrenade(
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

#endif //TP_WORMS_GREEN_GRANADE_H

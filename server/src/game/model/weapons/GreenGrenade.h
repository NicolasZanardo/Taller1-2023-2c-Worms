#ifndef TP_WORMS_GREEN_GRANADE_H
#define TP_WORMS_GREEN_GRANADE_H


#include "Weapon.h"

class GreenGrenade : public Weapon {
    int projectile_countdown;
    int default_projectile_countdown;
public:
    explicit GreenGrenade(
        int ammo_left,
        float max_damage,
        float explosion_radius,
        int default_count_down_time
    );

    void start_shooting(float from_x, float from_y, char facing_direction) override;

    void end_shooting(float from_x, float from_y, char facing_direction) override;

    bool change_projectile_count_down(ProjectileCountDown time) override;
    void on_turn_ended() override;
};


#endif //TP_WORMS_GREEN_GRANADE_H

#ifndef TP_WORMS_WEAPONROTATION_H
#define TP_WORMS_WEAPONROTATION_H

class WeaponRotation {
    bool is_aim_angle_rotating;
    bool is_aim_angle_rotating_upwards;
    const float max_weapon_rotation = 90;
public:
    WeaponRotation();
    float aimed_angle = 0;

    void start_aiming_up();
    void start_aiming_down();
    void stop_aiming_up();
    void stop_aiming_down();
    void on_update();
    void on_turn_ended();
};

#endif

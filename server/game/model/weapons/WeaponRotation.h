#ifndef TP_WORMS_WEAPONROTATION_H
#define TP_WORMS_WEAPONROTATION_H

class WeaponRotation {
    const float MAX_WEAPON_ROTATING = 90;
    bool is_aim_angle_rotating;
    bool is_aim_angle_rotating_upwards;
    float speed;
    float aimed_angle = 0;
public:
    WeaponRotation();

    void start_aiming_up();
    void start_aiming_down();
    void stop_aiming_up();
    void stop_aiming_down();
    void on_update();
    void on_turn_ended();
    float get_angle() const;
};

#endif

#ifndef TP_WORMS_WEAPON_H
#define TP_WORMS_WEAPON_H

#include <cstddef>
#include "../../core/Instance.h"
#include "WeaponRotation.h"

class Weapon {
    int ammo_left;
    float shoot_power;
    WeaponRotation weapon_rotation;

public:
    Weapon();
    void start_aiming_up();
    void start_aiming_down();
    void stop_aiming_up();
    void stop_aiming_down();
    void shoot();
    void on_update();
    void on_reset();
};


#endif //TP_WORMS_WEAPON_H

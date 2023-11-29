#include "WeaponRotation.h"
#include <iostream>

WeaponRotation::WeaponRotation() :
    is_aim_angle_rotating(false),
    is_aim_angle_rotating_upwards(false),
    speed(3.0f),
    aimed_angle(0)
    { }

void WeaponRotation::start_aiming_up() {
    is_aim_angle_rotating = true;
    is_aim_angle_rotating_upwards = true;
}

void WeaponRotation::start_aiming_down() {
    is_aim_angle_rotating = true;
    is_aim_angle_rotating_upwards = false;
}

void WeaponRotation::stop_aiming_up() {
    is_aim_angle_rotating = false; // TODO Better mechanics for when both are pressed/released
    is_aim_angle_rotating_upwards = false;
}

void WeaponRotation::stop_aiming_down() {
    is_aim_angle_rotating = false;
    is_aim_angle_rotating_upwards = false;
}

void WeaponRotation::on_update() {
    if (is_aim_angle_rotating) {
        // std::cout << "Rotation angle is: " << aimed_angle << std::endl;
        if (is_aim_angle_rotating_upwards && aimed_angle < MAX_WEAPON_ROTATING) {
            aimed_angle += speed;
        } else if (!is_aim_angle_rotating_upwards && aimed_angle > -MAX_WEAPON_ROTATING){
            aimed_angle -= speed;
        }
    }
}

void WeaponRotation::on_turn_ended() {
    is_aim_angle_rotating = false;
    is_aim_angle_rotating_upwards = false;
    aimed_angle = 0;
}

float WeaponRotation::get_angle() const {
    return aimed_angle;
}


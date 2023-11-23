#ifndef TP_WORMS_WEAPON_H
#define TP_WORMS_WEAPON_H

#include <cstddef>
#include <memory>
#include "../core/Instance.h"
#include "WeaponRotation.h"
#include "Damage.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../projectiles/Shot.h"


class Weapon {
protected:
    WeaponTypeDto type;
    int ammo_left;
    Damage damage;
    float shoot_power;
    bool has_shot_this_turn;
    WeaponRotation rotation;

    std::unique_ptr<Shot> c_shot;

public:
    Weapon(int ammo_left, Damage damage, float shoot_power, WeaponTypeDto type);
    void start_aiming_up();
    void start_aiming_down();
    void stop_aiming_up();
    void stop_aiming_down();
    virtual void start_shooting(float from_x, float from_y) = 0;
    virtual void end_shooting(float from_x, float from_y) = 0;
    void on_update();
    void on_turn_ended();
    std::unique_ptr<Shot> shot_component();

    virtual ~Weapon() {}
};


#endif //TP_WORMS_WEAPON_H
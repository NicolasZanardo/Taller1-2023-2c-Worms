#ifndef TP_WORMS_WEAPON_H
#define TP_WORMS_WEAPON_H

#include <cstddef>
#include <memory>
#include "../core/Instance.h"
#include "WeaponRotation.h"
#include "../../../../../common_base/Game/WeaponTypeDto.h"
#include "../projectiles/CShot.h"
#include "../../../../../common_base/Game/ProjectileCountDown.h"


class Weapon {
protected:
    WeaponTypeDto type;
    int ammo_left;
    float max_damage;
    float explosion_radius;
    float charged_power;
    const float max_power;
    bool has_shot_this_turn;
    WeaponRotation rotation;

    std::unique_ptr<CShot> c_shot;

public:
    Weapon(
        int ammo_left,
        float damage,
        const float max_power,
        float explosion_radius,
        WeaponTypeDto type
    );

    WeaponTypeDto WeaponType();

    float AimedAngle() const;

    void on_update();

    virtual void on_turn_ended();

    virtual void start_shooting(float from_x, float from_y, char facing_sign) = 0;

    virtual void end_shooting(float from_x, float from_y, char facing_sign) = 0;

    void start_aiming_up();

    void start_aiming_down();

    void stop_aiming_up();

    void stop_aiming_down();

    virtual bool change_projectile_count_down(ProjectileCountDown count_down) = 0;

    std::unique_ptr<CShot> shot_component();

    virtual ~Weapon() {}
};


#endif //TP_WORMS_WEAPON_H

#ifndef TP_WORMS_WEAPON_H
#define TP_WORMS_WEAPON_H

#include <cstddef>
#include <memory>
#include "Instance.h"
#include "WeaponRotation.h"
#include "WeaponTypeDto.h"
#include "CShot.h"
#include "ProjectileCountDown.h"
#include "WeaponCfg.h"

class Weapon {
protected:
    WeaponTypeDto type;
    int ammo_left;
    float max_damage;
    float max_shoot_power;
    float explosion_radius;
    float projectile_radius;
    bool affected_by_wind;
    bool has_shot_this_turn;
    WeaponRotation rotation;

    std::unique_ptr<CShot> c_shot;

    explicit Weapon(WeaponCfg & weapon_cfg);
public:

    WeaponTypeDto WeaponType();

    float AimedAngle() const;

    virtual void on_update(int it, int rate);

    virtual void on_turn_ended();

    virtual void start_shooting(float from_x, float from_y, char facing_sign) = 0;

    virtual void end_shooting(float from_x, float from_y, char facing_sign) = 0;

    virtual bool change_projectile_count_down(ProjectileCountDown count_down) = 0;

    void start_aiming_up();

    void start_aiming_down();

    void stop_aiming_up();

    void stop_aiming_down();

    std::unique_ptr<CShot> shot_component();

    virtual ~Weapon() = default;
};


#endif //TP_WORMS_WEAPON_H

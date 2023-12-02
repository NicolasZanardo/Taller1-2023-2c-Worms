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
#include "ProjectileCountDownChanger.h"

class Weapon {
protected:
    ProjectileCfg projectile_data;
    WeaponTypeDto type;
    int ammo_left;
    float max_shoot_power;
    bool has_shot_this_turn;
    WeaponRotation rotation;
    std::unique_ptr<ProjectileCountDownChanger> countdown_changer;

    std::unique_ptr<CShot> c_shot;

    explicit Weapon(WeaponCfg & weapon_data, std::unique_ptr<ProjectileCountDownChanger> projectile_countdown_changer);
    virtual std::unique_ptr<CShot> shoot(float from_x, float from_y, char facing_sign);

public:

    WeaponTypeDto WeaponType();

    float AimedAngle() const;

    virtual void on_update(int it, int rate);

    virtual void on_turn_ended();

    virtual void start_shooting(float from_x, float from_y, char facing_sign) = 0;

    virtual void end_shooting(float from_x, float from_y, char facing_sign) = 0;

    void change_projectile_count_down(ProjectileCountDown count_down);

    void start_aiming_up();

    void start_aiming_down();

    void stop_aiming_up();

    void stop_aiming_down();

    std::unique_ptr<CShot> shot_component();

    virtual ~Weapon() = default;
};


#endif //TP_WORMS_WEAPON_H

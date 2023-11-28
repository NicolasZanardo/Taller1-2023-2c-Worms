#ifndef TP_WORMS_GREEN_GRANADE_H
#define TP_WORMS_GREEN_GRANADE_H

#include "ChargeableWeapon.h"
#include "../../../core/configs/model/WeaponCfg.h"

class GreenGrenade : public ChargeableWeapon {
    const int default_projectile_countdown;
    int projectile_countdown;
public:
    explicit GreenGrenade(WeaponCfg &weapon_cfg);

    bool change_projectile_count_down(ProjectileCountDown time) override;
    void on_turn_ended() override;
    std::unique_ptr<CShot> shoot(float charged_power, float from_x, float from_y, char facing_sign) override;
};

#endif //TP_WORMS_GREEN_GRANADE_H

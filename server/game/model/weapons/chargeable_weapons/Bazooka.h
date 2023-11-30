#ifndef TP_WORMS_BAZOOKA_H
#define TP_WORMS_BAZOOKA_H

#include "ChargeableWeapon.h"
#include "WeaponCfg.h"

class Bazooka : public ChargeableWeapon {
public:
    explicit Bazooka(WeaponCfg &weapon_cfg);

    std::unique_ptr<CShot> shoot(float charged_power, float from_x, float from_y, char facing_sign) override;

    bool change_projectile_count_down(ProjectileCountDown time) override;
};


#endif //TP_WORMS_BAZOOKA_H
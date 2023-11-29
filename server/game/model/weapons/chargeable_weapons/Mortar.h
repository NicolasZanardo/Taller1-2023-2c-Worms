#ifndef TP_WORMS_MORTAR_H
#define TP_WORMS_MORTAR_H

#include "Weapon.h"
#include "ChargeableWeapon.h"
#include "WeaponCfg.h"

class Mortar: public ChargeableWeapon {
public:
    explicit Mortar(WeaponCfg &weapon_cfg);

    bool change_projectile_count_down(ProjectileCountDown time) override;
    std::unique_ptr<CShot> shoot(float charged_power, float from_x, float from_y, char facing_sign) override;
};

#endif //TP_WORMS_MORTAR_H

#ifndef TP_WORMS_INSTANT_WEAPON_EXAMPLE_H
#define TP_WORMS_INSTANT_WEAPON_EXAMPLE_H

#include "InstantShotWeapon.h"

class InstantWeaponExample : public InstantShotWeapon {
public:
    explicit InstantWeaponExample(WeaponCfg &cfg);

    bool change_projectile_count_down(ProjectileCountDown time) override;
    std::unique_ptr<CShot> shoot(float from_x, float from_y, char facing_sign) override;
};

#endif

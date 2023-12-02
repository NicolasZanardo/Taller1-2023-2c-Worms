#ifndef TP_WORMS_INSNTANTSHOTWEAPON_H
#define TP_WORMS_INSNTANTSHOTWEAPON_H

#include "Weapon.h"

class InstantShotWeapon: public Weapon {
    friend class WeaponFactory;

    void start_shooting(float from_x, float from_y, char facing_sign) final;
    void end_shooting(float from_x, float from_y, char facing_sign) final;
protected:
    explicit InstantShotWeapon(WeaponCfg &cfg, std::unique_ptr<ProjectileCountDownChanger> countdown_changer);
};

#endif //TP_WORMS_INSNTANTSHOTWEAPON_H

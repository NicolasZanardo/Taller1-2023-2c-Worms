#ifndef TP_WORMS_INSNTANTSHOTWEAPON_H
#define TP_WORMS_INSNTANTSHOTWEAPON_H

#include "../Weapon.h"

class InstantShotWeapon: public Weapon {

    void start_shooting(float from_x, float from_y, char facing_sign) final;
    void end_shooting(float from_x, float from_y, char facing_sign) final;
protected:
    InstantShotWeapon(
        int ammo_left,
        float damage,
        float explosion_radius,
        WeaponTypeDto type
        );
    virtual std::unique_ptr<CShot> shoot(float from_x, float from_y, char facing_sign) = 0;
};

#endif //TP_WORMS_INSNTANTSHOTWEAPON_H

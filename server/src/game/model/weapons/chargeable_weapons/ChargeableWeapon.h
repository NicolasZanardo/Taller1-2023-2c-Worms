#ifndef TP_WORMS_CHARGEABLEWEAPON_H
#define TP_WORMS_CHARGEABLEWEAPON_H

#include "Weapon.h"

class ChargeableWeapon: public Weapon {
    void on_update(const int it, const int rate) override;
    void start_shooting(float from_x, float from_y, char facing_sign) override;
    void end_shooting(float from_x, float from_y, char facing_sign) final;
protected:
    float charged_power;
    const float max_power = 1;
    const float charging_duration = 2.0;
    bool is_charging;
    float started_charge_at_x;
    float started_charge_at_y;
    char facing_sign_when_started_charge;

    ChargeableWeapon(
        int ammo_left,
        float damage,
        float explosion_radius,
        WeaponTypeDto type
    );
public:
    void virtual on_end_shooting(float from_x, float from_y, char facing_sign) = 0;
};


#endif //TP_WORMS_CHARGEABLEWEAPON_H

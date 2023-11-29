#ifndef TP_WORMS_CHARGEABLEWEAPON_H
#define TP_WORMS_CHARGEABLEWEAPON_H

#include "Weapon.h"
#include "WeaponCfg.h"

class ChargeableWeapon : public Weapon {
    const float MAX_POWER = 1;
    const float CHARGING_DURATION = 2000;
    float charged_power;
    bool is_charging;
    float started_charge_at_x;
    float started_charge_at_y;
    char facing_sign_when_started_charge;

    void on_update(const int it, const int rate) final;

    void start_shooting(float from_x, float from_y, char facing_sign) final;

    void end_shooting(float from_x, float from_y, char facing_sign) final;

protected:
    void on_turn_ended() override;

    explicit ChargeableWeapon(WeaponCfg &cfg);

public:
    virtual std::unique_ptr<CShot> shoot(float charged_power, float from_x, float from_y, char facing_sign) = 0;
};


#endif //TP_WORMS_CHARGEABLEWEAPON_H

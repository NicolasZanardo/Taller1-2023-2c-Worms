#ifndef TP_WORMS_CHARGEABLEWEAPON_H
#define TP_WORMS_CHARGEABLEWEAPON_H

#include "Weapon.h"
#include "WeaponCfg.h"

class ChargeableWeapon : public Weapon {
    friend class WeaponFactory;
    const float MAX_POWER = 1;
    const int time_to_fully_charge;
    float charged_percentage;
    bool is_charging;
    float started_charge_at_x;
    float started_charge_at_y;
    char facing_sign_when_started_charge;

    void on_update(const int it, const int rate) final;

    void start_shooting(float from_x, float from_y, char facing_sign) final;

    void end_shooting(float from_x, float from_y, char facing_sign) final;

protected:
    void on_turn_ended() override;

    explicit ChargeableWeapon(WeaponCfg &cfg, std::unique_ptr<ProjectileCountDownChanger> projectile_countdown_changer);

public:
    std::unique_ptr<CShot> shoot(float from_x, float from_y, char facing_sign) override;
};


#endif //TP_WORMS_CHARGEABLEWEAPON_H

#include "WeaponFactory.h"
#include "InstantShotWeapon.h"
#include "DefaultProjectileCountDownChanger.h"
#include "NoneProjectileCountDownChanger.h"
#include "ChargeableWeapon.h"

std::shared_ptr<Weapon> WeaponFactory::create(WeaponCfg &weapon_cfg) {

    std::unique_ptr<ProjectileCountDownChanger> projectile_count_down_changer = nullptr;
    if (weapon_cfg.projectile.default_explosion_countdown > 0) {
        projectile_count_down_changer = std::make_unique<DefaultProjectileCountdownChanger>(
            weapon_cfg.projectile.default_explosion_countdown
            );
    } else {
        projectile_count_down_changer = std::make_unique<NoneProjectileCountDownChanger>(0);
    }

    if (weapon_cfg.charge.has_value()) {
        return std::shared_ptr<ChargeableWeapon>( new ChargeableWeapon(weapon_cfg, std::move(projectile_count_down_changer)));
    } else {
        return std::shared_ptr<InstantShotWeapon>( new InstantShotWeapon(weapon_cfg, std::move(projectile_count_down_changer)));
    }

}

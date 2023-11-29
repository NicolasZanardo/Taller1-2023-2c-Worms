#include "GreenGrenade.h"
#include <iostream>

GreenGrenade::GreenGrenade(WeaponCfg& cfg):
    ChargeableWeapon(cfg),
    default_projectile_countdown(cfg.default_projectile_countdown),
    projectile_countdown(default_projectile_countdown) {}

std::unique_ptr<CShot> GreenGrenade::shoot(float charged_power, float from_x, float from_y, char facing_sign) {
    return std::make_unique<CShot>(
        std::make_unique<ProjectileInfo>(
            rotation.get_angle(),
            facing_sign,
            max_damage,
            explosion_radius,
            charged_power * max_shoot_power,
            from_x,
            from_y,
            projectile_radius,
            affected_by_wind,
            projectile_countdown,
            ProjectileTypeDto::GREEN_GRENADE, // TODO WEAPONCFG CAN HAVE THE PROJECTILE IT SHOOTS
            nullptr // TODO WEAPON CFG CAN DINAMICALLY MADE WEAPONS EXPLODE FRAG?
        )
    );
}

bool GreenGrenade::change_projectile_count_down(ProjectileCountDown time) {
    projectile_countdown = static_cast<int>(time);
    return true;
}

void GreenGrenade::on_turn_ended() {
    ChargeableWeapon::on_turn_ended();
    projectile_countdown = default_projectile_countdown;
}

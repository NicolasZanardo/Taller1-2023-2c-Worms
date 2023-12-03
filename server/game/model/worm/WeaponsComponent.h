#ifndef TP_WORMS_WEAPONCOMPONENT_H
#define TP_WORMS_WEAPONCOMPONENT_H

#include <map>
#include <memory>
#include "Weapon.h"
#include "Config.h"

typedef std::map<WeaponTypeDto, std::shared_ptr<Weapon>> WeaponMap;

class WeaponsComponent {
    WeaponMap weapons;
    std::shared_ptr<Weapon> actual_weapon;

public:

    explicit WeaponsComponent(Config<WeaponCfg> &weapons_cfg);

    std::unique_ptr<CShot> shot_component();

    static WeaponMap create_default_weapons(Config<WeaponCfg> &weapons_cfg);

    void update(int it, int rate);
    void on_turn_ended();

    WeaponTypeDto WeaponType() const;
    float AimedAngle() const;

    void start_aiming_down();
    void start_aiming_up();
    void stop_aiming_up();
    void stop_aiming_down();
    void do_weapon_primary_action(float from_x, float from_y, char facing_sign);
    void do_weapon_secondary_action(float from_x, float from_y, char facing_sign);
    void change_weapon(WeaponTypeDto weapon);
    void change_projectile_count_down(ProjectileCountDown count_down);

};


#endif //TP_WORMS_WEAPONCOMPONENT_H

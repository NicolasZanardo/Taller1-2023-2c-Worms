#ifndef TP_WORMS_WEAPONFACTORY_H
#define TP_WORMS_WEAPONFACTORY_H

#include <memory>
#include "Weapon.h"
#include "WeaponCfg.h"

class WeaponFactory {
public:
    WeaponFactory() = delete;
    WeaponFactory(const WeaponFactory&) = delete;
    WeaponFactory& operator=(const WeaponFactory&) = delete;
    WeaponFactory(WeaponFactory&& other) = delete;
    WeaponFactory& operator=(WeaponFactory&& other) = delete;

    static std::shared_ptr<Weapon> create(WeaponCfg& weapon_cfg);
};


#endif //TP_WORMS_WEAPONFACTORY_H

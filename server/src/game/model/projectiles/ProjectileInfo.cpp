#include "ProjectileInfo.h"

ProjectileInfo::ProjectileInfo(Damage &damage, float power, float origin_x, float origin_y, WeaponTypeDto from_weapon) :
        damage(damage),
        power(power),
        origin_x(origin_x),
        origin_y(origin_y),
        from_weapon(from_weapon)
        {}
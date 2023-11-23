#include "Projectile.h"

Projectile::Projectile(Damage &damage, float power, float origin_x, float origin_y) :
        damage(damage),
        power(power),
        origin_x(origin_x),
        origin_y(origin_y)
        {}
#include <iostream>
#include "ProjectileFactory.h"
#include "CountdownProjectile.h"
#include "InstantExplosionProjectile.h"

std::shared_ptr<Projectile> ProjectileFactory::create_projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info) {
    if (info->countdown <= 0) {
        return std::shared_ptr<InstantExplosionProjectile>(new InstantExplosionProjectile(id, info));
    } else {
        return std::shared_ptr<CountdownProjectile>(new CountdownProjectile(id, info));
    }
}

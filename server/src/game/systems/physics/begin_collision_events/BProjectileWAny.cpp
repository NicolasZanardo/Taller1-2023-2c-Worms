#include "BProjectileWAny.h"
#include "../../../model/projectiles/Projectile.h"

void BProjectileWAny::resolve(Collidable *projectile_collidable, Collidable *any) {
    auto projectile = dynamic_cast<Projectile*>(projectile_collidable);

    if (projectile != nullptr && !projectile->has_exploded()) {
        projectile->on_collision();
    }
}

void BProjectileWAny::resolve_inverse(Collidable *any, Collidable *projectile_collidable) {
    resolve(projectile_collidable, any);
}



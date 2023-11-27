#include "BProjectileWAny.h"
#include "../../../model/projectiles/Projectile.h"

void BProjectileWAny::resolve(Collidable *projectile_collidable, Collidable *any, b2Contact* contact) {
    auto projectile = dynamic_cast<Projectile*>(projectile_collidable);

    if (projectile != nullptr && !projectile->has_exploded()) {
        b2WorldManifold world_manifold;
        contact->GetWorldManifold(&world_manifold);
        projectile->on_collision(world_manifold.points[0]);
    }
}

void BProjectileWAny::resolve_inverse(Collidable *any, Collidable *projectile_collidable, b2Contact* contact) {
    resolve(projectile_collidable, any, contact);
}



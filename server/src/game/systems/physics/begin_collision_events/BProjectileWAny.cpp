#include <iostream>
#include "BProjectileWAny.h"
#include "../../../model/projectiles/Projectile.h"
#include "../../../core/Logger.h"

void BProjectileWAny::resolve(Collidable *projectile_collidable, Collidable *any, b2Manifold* manifold) {
    auto projectile = dynamic_cast<Projectile*>(projectile_collidable);

    b2Vec2 explosion_point;

    if (manifold->type == b2Manifold::e_circles) {
        // For circles Projectile - worm case
        Logger::log_position("Projectile center at collision", projectile->X(), projectile->Y());
        explosion_point = manifold->points[0].localPoint;
        Logger::log_position("Explosion center", explosion_point.x, explosion_point.y);

    } else if (manifold->type == b2Manifold::e_faceA || manifold->type == b2Manifold::e_faceB) {
        // Circle collides with a polygon (e.g., ground), use the contact point
        Logger::log_position("Projectile center at collision not circle", projectile->X(), projectile->Y());
        std::cout << manifold->localPoint.x << std::endl;
        std::cout << manifold->localPoint.y << std::endl;
    }

    if (projectile != nullptr && !projectile->has_exploded()) {
        projectile->on_collision(explosion_point);
    }
}

void BProjectileWAny::resolve_inverse(Collidable *any, Collidable *projectile_collidable, b2Manifold* manifold) {
    resolve(projectile_collidable, any, manifold);
}



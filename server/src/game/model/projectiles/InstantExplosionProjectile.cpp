#include "InstantExplosionProjectile.h"

InstantExplosionProjectile::InstantExplosionProjectile(size_t id, const std::unique_ptr<ProjectileInfo> &info): Projectile(id, info) {}

void InstantExplosionProjectile::on_collision(b2Vec2 collision_point) {
    if (!exploded) {
        explode();
    }
}
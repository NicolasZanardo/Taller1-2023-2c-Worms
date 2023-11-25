#include "BProjectileWithAny.h"
#include "../../../model/projectiles/Projectile.h"
#include "../../../core/Logger.h"
#include <iostream>

bool BProjectileWithAny::try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) {
    auto *projectile = query.get_object_from_fixture<Projectile>(fixtureA, fixtureB);
    if (projectile != nullptr && !projectile->has_exploded()) {
        b2Vec2 center = projectile->B2Body()->GetPosition();
        Logger::log_position("Projectile collided", center.x, center.y);

        for (int i = 0; i < num_rays; i++) {
            // Convert degrees to radians
            // float angle = (i / (float)num_rays) * 360 * M_PI / 180.0f;
            float angle = (i * 2 * M_PI) / num_rays;
            b2Vec2 rayDir(sinf(angle), cosf(angle));
            // Logger::log_position("Ray dir", rayDir.x, rayDir.y);
            b2Vec2 rayEnd = center + projectile->ExplosionRadius() * rayDir;
            // Logger::log_position("Ray end", rayEnd.x, rayEnd.y);
            world.RayCast(&onExplosionRayCast, center, rayEnd);
            for (auto worm_hit: onExplosionRayCast.worms_hit) {
                apply_blast_impulse(worm_hit.worm->B2Body(), center, worm_hit.hit_point,
                                    (blastPower / (float) num_rays));
                if (unique_worms.find(worm_hit.worm) == unique_worms.end()) {
                    worm_hit.worm->receive_damage(projectile->damage);
                    unique_worms.insert(worm_hit.worm);
                }
            }
        }
        unique_worms.clear();
        projectile->on_collision();
        return true;
    }

    return false;
}

BProjectileWithAny::BProjectileWithAny(b2World &world) : CollisionEvent(world), onExplosionRayCast(query) {}

void BProjectileWithAny::apply_blast_impulse(b2Body *body, b2Vec2 blast_center, b2Vec2 apply_point, float blast_power) {
    b2Vec2 blast_dir = apply_point - blast_center;
    float distance = blast_dir.Normalize();
    //ignore bodies exactly at the blast point - blast direction is undefined
    if (distance == 0)
        return;
    float inv_distance = 1 / distance;
    float impulse_mag = blast_power * inv_distance * inv_distance;
    body->ApplyLinearImpulse(impulse_mag * blast_dir, apply_point, true);
} // TODO Have a max limit for the impulse?



#include "BProjectileWithAny.h"
#include "../../../model/projectiles/Projectile.h"
#include <iostream>

bool BProjectileWithAny::try_resolve(b2Fixture *fixtureA, b2Fixture *fixtureB) {
    auto* projectile = query.get_object_from_fixture<Projectile>(fixtureA, fixtureB);
    if (projectile != nullptr && !projectile->has_exploded()) {
        std::cout << "A projectile has just collided\n";
        b2Vec2 center = projectile->B2Body()->GetPosition();

        for (int i = 0; i < num_rays; i++) {
            // Convert degrees to radians
            float angle = (i / (float)num_rays) * 360 * M_PI / 180.0f;;
            b2Vec2 rayDir( sinf(angle), cosf(angle) );
            b2Vec2 rayEnd = center + projectile->ExplosionRadius() * rayDir;

            world.RayCast(&onExplosionRayCast, center, rayEnd);
            if ( onExplosionRayCast.worm ) {
                apply_blast_impulse(onExplosionRayCast.worm->B2Body(), center, onExplosionRayCast.ray_cast_hit_point, (blastPower / (float)num_rays));
                if (hit_worms.find(onExplosionRayCast.worm) == hit_worms.end()) {
                    onExplosionRayCast.worm->receive_damage(projectile->damage);
                    hit_worms.insert(onExplosionRayCast.worm);
                }
                // TODO Damage should be according to distance
            }
        }
        projectile->on_collision();
        hit_worms.clear();
        return true;
    }
    return false;
}

BProjectileWithAny::BProjectileWithAny(b2World &world) : CollisionEvent(world), onExplosionRayCast(query)  {}

void BProjectileWithAny::apply_blast_impulse(b2Body* body, b2Vec2 blast_center, b2Vec2 apply_point, float blast_power) {
    b2Vec2 blast_dir = apply_point - blast_center;
    float distance = blast_dir.Normalize();
    //ignore bodies exactly at the blast point - blast direction is undefined
    if ( distance == 0 )
        return;
    float inv_distance = 1 / distance;
    float impulse_mag = blast_power * inv_distance * inv_distance;
    body->ApplyLinearImpulse(impulse_mag * blast_dir, apply_point, true);
} // TODO Have a max limit for the impulse?



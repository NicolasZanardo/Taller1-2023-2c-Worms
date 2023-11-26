#include "BProjectileWAny.h"
#include "../../../model/projectiles/Projectile.h"
#include "../query_callbacks/ProjectileExplosionQueryCallback.h"


void BProjectileWAny::apply_blast_impulse(b2Body *body, b2Vec2 blast_dir, b2Vec2 apply_point, float distance) {
    //ignore bodies exactly at the blast point - blast direction is undefined
    if (distance == 0)
        return;

    float impulse_mag = explosion_power * (1 / distance);
    body->ApplyLinearImpulse(impulse_mag * blast_dir, apply_point, true);
}

void BProjectileWAny::resolve(Collidable *projectile_collideable, Collidable *any) {
    auto projectile = dynamic_cast<Projectile*>(projectile_collideable);

    if (projectile != nullptr && !projectile->has_exploded()) {
        b2Vec2 explosion_point = projectile->B2Body()->GetPosition();
        std::cout << "Correctly casting projectile\n";
        // Logger::log_position("Projectile collided", explosion_point.x, explosion_point.y);
        float explosion_radius = projectile->explosion_radius;
        float max_damage = projectile->damage;

        ProjectileExplosionQueryCallback query_callback;
        b2AABB aabb;
        aabb.lowerBound = explosion_point - b2Vec2(explosion_radius, explosion_radius );
        aabb.upperBound = explosion_point + b2Vec2(explosion_radius, explosion_radius );

        projectile->B2Body()->GetWorld()->QueryAABB(&query_callback, aabb);

        //check which of these worms have their center of mass within the blast radius
        for (auto [_, worm]: query_callback.found_worms_map) {
            b2Body* body = worm->B2Body();
            b2Vec2 body_center_mass = body->GetWorldCenter();

            //ignore worms outside the explosion radius
            b2Vec2 blast_dir = body_center_mass - explosion_point;
            float distance = blast_dir.Length();
            if (distance >= explosion_radius)
                continue;

            float damage = max_damage * (1.0f - distance / explosion_radius);
            worm->receive_damage(damage);

            apply_blast_impulse(body, explosion_point, body_center_mass, distance );
        }

        projectile->on_collision();
    }
}

void BProjectileWAny::resolve_inverse(Collidable *any, Collidable *projectile_collideable) {
    resolve(projectile_collideable, any);
}



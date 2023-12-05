#include "OnExplosionWormsQuery.h"
#include "ExplosionQueryCallback.h"
#include "ExplosionForce.h"


void OnExplosionWormsQuery::act_on_found(b2World& world, std::unique_ptr<CExplosion> explosion) {
    b2Vec2 explosion_point = b2Vec2(explosion->x, explosion->y);
    // Logger::log_position("Projectile collided", explosion_point.x, explosion_point.y);

    ExplosionQueryCallback query_callback;
    b2AABB aabb;
    aabb.lowerBound = explosion_point - b2Vec2( explosion->radius,  explosion->radius);
    aabb.upperBound = explosion_point + b2Vec2( explosion->radius,  explosion->radius);

    world.QueryAABB(&query_callback, aabb);

    //check which of these worms have their center of mass within the blast radius
    for (auto [_, worm]: query_callback.found_worms_map) {
        b2Body* body = worm->B2Body();
        b2Vec2 body_center_mass = body->GetWorldCenter();

        //ignore worms outside the explosion radius
        b2Vec2 blast_dir = body_center_mass - explosion_point;
        float distance = blast_dir.Length();
        distance -= (WORM_SIZE / 2); // Adjust with the worm radius from the center of body mass
        if (distance >= explosion->radius)
            continue;

        // At max distance (distance / explosion->radius) = 1 -> max_damage * 0
        // At min distance (distance / explosion->radius) = 0 -> max_damage * 1
        float damage = explosion->max_damage * (1.0f - distance / explosion->radius);
        worm->receive_damage(damage);
        ExplosionForce force(world, explosion_point, explosion->radius);
        worm->receive_force(force);
    }
}

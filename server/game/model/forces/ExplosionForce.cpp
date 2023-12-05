#include "ExplosionForce.h"
#include "constants.h"

ExplosionForce::ExplosionForce(
    b2World &world,
    b2Vec2 explosion_point,
    float explosion_radius
) : Force(world), explosion_point(explosion_point), explosion_radius(explosion_radius) {}

void ExplosionForce::apply(b2Body *body) {
    b2Vec2 apply_point = body->GetWorldCenter();
    b2Vec2 blast_dir = apply_point - explosion_point;
    float distance = blast_dir.Normalize();
    distance -= (WORM_SIZE / 2); // Adjust distance with worm radius
    if (distance == 0)
        return;
    // At max distance (distance / explosion->radius) = 1 -> EXPLOSION_POWER * 0
    // At min distance (distance / explosion->radius) = 0 -> EXPLOSION_POWER * 1
    float impulse_mag = EXPLOSION_POWER * (1.0f - distance / explosion_radius);
    // float impulse_mag = EXPLOSION_POWER * (1 / distance);
    if (impulse_mag > MAX_IMPULSE) {
        impulse_mag = MAX_IMPULSE;
    }

    body->ApplyLinearImpulse(impulse_mag * blast_dir, body->GetWorldCenter(), true);
}

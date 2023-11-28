#include "ExplosionForce.h"

ExplosionForce::ExplosionForce(b2World &world, b2Vec2 explosion_point) : Force(world), explosion_point(explosion_point) {}

void ExplosionForce::apply(b2Body *body) {
    b2Vec2 apply_point = body->GetWorldCenter();
    b2Vec2 blast_dir = apply_point - explosion_point;
    float distance = blast_dir.Normalize();
    if (distance == 0)
        return;
    float impulse_mag = EXPLOSION_POWER * (1 / distance) * (1 / distance);
    body->ApplyLinearImpulse(impulse_mag * blast_dir, body->GetWorldCenter(), true);
}

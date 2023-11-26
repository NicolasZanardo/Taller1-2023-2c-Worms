#include "BuoyancyForce.h"

BuoyancyForce::BuoyancyForce(b2World &world): Force(world) {}

void BuoyancyForce::apply(b2Body *body) {
    b2Vec2 gravity = world.GetGravity();
    float buoyancy_force_magnitude = -gravity.y * body->GetMass();

    // Apply additional damping to simulate water resistance
    b2Vec2 damping_force = -0.1f * body->GetLinearVelocity();

    // Apply the combined buoyancy and damping forces
    b2Vec2 buoyancy_force(0.0f, buoyancy_force_magnitude);
    b2Vec2 total_force = buoyancy_force + damping_force;

    // Apply the force at the center of the body
    body->ApplyForce(total_force, body->GetWorldCenter(), true);
}

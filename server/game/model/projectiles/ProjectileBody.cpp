#include "ProjectileBody.h"
#include "BuoyancyForce.h"
#include <cmath>

ProjectileBody::ProjectileBody(
    b2World &world,
    b2Body *body,
    bool is_facing_right
) : Body(world, body, is_facing_right), spawned_facing_right(is_facing_right), is_on_water(false) {}

void ProjectileBody::sink() {
    is_on_water = true;
}

bool ProjectileBody::did_spawned_facing_right() const {
    return spawned_facing_right;
}

void ProjectileBody::on_update() {
    update_rotation();
    if (is_on_water) {
        BuoyancyForce force(world);
        receive(force);
    }
}

void ProjectileBody::update_rotation() {
    b2Vec2 velocity = body->GetLinearVelocity();
    auto angle = std::atan2(velocity.y, velocity.x);
    // Adjust the angle if the projectile was shot left
    if (!spawned_facing_right) {
        angle = M_PI - angle;
    }

    body->SetTransform(body->GetWorldCenter(), angle);
}


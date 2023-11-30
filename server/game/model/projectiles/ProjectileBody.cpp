#include "ProjectileBody.h"
#include "BuoyancyForce.h"
#include "RotationStrategy.h"
#include <iostream>

ProjectileBody::ProjectileBody(
    b2World &world,
    b2Body *body,
    bool is_facing_right,
    std::unique_ptr<RotationStrategy> rotation_strategy
) : Body(world, body, is_facing_right),
    spawned_facing_right(is_facing_right),
    is_on_water(false),
    rotation_strategy(std::move(rotation_strategy)) {}

void ProjectileBody::sink() {
    is_on_water = true;
}

bool ProjectileBody::did_spawned_facing_right() const {
    return spawned_facing_right;
}

void ProjectileBody::on_update() {
    if (rotation_strategy) {
        rotation_strategy->update_rotation(body);
    }
    if (is_on_water) {
        BuoyancyForce force(world);
        receive(force);
    }
}

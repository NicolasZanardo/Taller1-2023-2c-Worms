#include "ProjectileBody.h"
#include "BuoyancyForce.h"

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
    if (is_on_water) {
        BuoyancyForce force(world);
        receive(force);
    }
}

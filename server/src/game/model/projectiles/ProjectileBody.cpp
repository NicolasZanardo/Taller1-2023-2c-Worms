#include "ProjectileBody.h"
#include "../forces/BuoyancyForce.h"

ProjectileBody::ProjectileBody(b2World& world, b2Body *body) : Body(world, body), is_on_water(false) {}

void ProjectileBody::sink() {
    is_on_water = true;
}

void ProjectileBody::on_update() {
    if(is_on_water) {
        BuoyancyForce force(world);
        force.apply(this->body);
    }
}

#include "RotationStrategy.h"
#include <cmath>

void VelocityAlignedRotation::update_rotation(b2Body *body) const {
    b2Vec2 velocity = body->GetLinearVelocity();
    auto angle = std::atan2(velocity.y, velocity.x);

    body->SetTransform(body->GetWorldCenter(), angle);
}

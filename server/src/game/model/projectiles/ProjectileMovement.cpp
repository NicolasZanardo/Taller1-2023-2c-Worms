#include "ProjectileMovement.h"

ProjectileMovement::ProjectileMovement(b2Body* body): body(body) {}

float ProjectileMovement::X() const {
    return body->GetPosition().x;
}

float ProjectileMovement::Y() const {
    return body->GetPosition().y;
}

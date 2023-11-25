#include "Damage.h"

Damage::Damage(const float damage, const float radius): damage(damage), radius(radius) {}

float Damage::Radius() const {
    return radius;
}

float Damage::Amount() const {
    return damage;
}

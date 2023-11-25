#include "Health.h"

Health::Health(float initial_health): actual_health(initial_health), is_alive(actual_health > 0) {}

void Health::on_update() {}

bool Health::IsAlive() const {
    return is_alive;
}

float Health::Amount() const {
    return actual_health;
}

bool Health::heal(float amount) {
    actual_health += amount;
}

void Health::receive_damage(float damage) {
    actual_health -= damage;
    if (actual_health <= 0) {
        is_alive = false;
    }
}

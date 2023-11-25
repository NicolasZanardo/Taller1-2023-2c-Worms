#include "Health.h"

Health::Health(float initial_health): actual_health(initial_health), is_alive(actual_health > 0) {}

void Health::on_update() {}

bool Health::IsAlive() {
    return is_alive;
}

bool Health::Amount() {
    return actual_health;
}

bool Health::heal(float amount) {
    actual_health += amount;
}

void Health::receive_damage(Damage &damage) {
    actual_health -= damage.Amount();
    if (actual_health <= 0) {
        is_alive = false;
    }
}

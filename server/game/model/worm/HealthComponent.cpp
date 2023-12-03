#include "HealthComponent.h"
#include "Worm.h"
#include <iostream>
HealthComponent::HealthComponent(float initial_health): actual_health(initial_health), is_dead(false), water_death_timer(WATER_DEATH_TIME) {}

bool HealthComponent::update(const std::shared_ptr<Worm>& worm, const int it, const int rate) {
    if (is_dead) {
        worm->Destroy();
        return false;
    }
    if (worm->is_on_water) {
        water_death_timer -= it * rate;
        if (water_death_timer <= 0) {
            die(worm);
            return false;
        }
    }
    return true;
}

float HealthComponent::amount() const {
    return actual_health;
}

void HealthComponent::adjust_health_to(float amount) {
    actual_health = amount;
}

bool HealthComponent::receive_damage(float damage) {
    actual_health -= damage;
    if (actual_health <= 0) {
        actual_health = 0;
        is_dead = true;
        return true;
    }
    return false;
}

void HealthComponent::die(const std::shared_ptr<Worm>& worm) {
    actual_health = 0;
    is_dead = true;
    worm->state = WormStateDto::DEAD;
}

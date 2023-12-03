#include "HealthComponent.h"
#include "Worm.h"

HealthComponent::HealthComponent(float initial_health): actual_health(initial_health), is_dead(false), water_death_timer(WATER_DEATH_TIME), on_cheat_mode(false) {}

bool HealthComponent::update(const std::shared_ptr<Worm>& worm, const int it, const int rate) {
    if (is_dead) {
        std::cout << "Now is dead so ill destroy the instance\n";
        worm->Destroy();
        return false;
    }
    if (worm->is_on_water && !on_cheat_mode) {
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
    if (!on_cheat_mode) {
        actual_health -= damage;
        if (actual_health <= 0) {
            std::cout << "Died\n";
            actual_health = 0;
            is_dead = true;
            return true;
        }
        return false;
    }
    return false;
}

void HealthComponent::die(const std::shared_ptr<Worm>& worm) {
    actual_health = 0;
    is_dead = true;
    worm->state = WormStateDto::DEAD;
}

void HealthComponent::toggle_cheat_mode() {
    on_cheat_mode = !on_cheat_mode;
}




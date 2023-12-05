#ifndef TP_WORMS_HEALTHCOMPONENT_H
#define TP_WORMS_HEALTHCOMPONENT_H

#include <memory>

class Worm;

class HealthComponent {
    int WATER_DEATH_TIME = 1500;
    float actual_health;
    bool is_dead;
    int water_death_timer;
    bool on_cheat_mode;

public:
    explicit HealthComponent(float initial_health);
    bool update(const std::shared_ptr<Worm>& worm, const int it, const int rate);
    float amount() const;

    bool receive_damage(float damage);
    void adjust_health_to(float amount);

    void die(const std::shared_ptr<Worm>& worm);

    void toggle_cheat_mode();

};


#endif //TP_WORMS_HEALTHCOMPONENT_H

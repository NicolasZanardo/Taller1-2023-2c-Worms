#ifndef TP_WORMS_HEALTH_H
#define TP_WORMS_HEALTH_H

#include <memory>

class Health {
    float actual_health;
    bool is_alive;

public:
    explicit Health(float initial_health);
    void on_update();
    bool IsAlive() const;
    float Amount() const;

    void receive_damage(float damage);
    void heal(float amount);

};


#endif //TP_WORMS_HEALTH_H

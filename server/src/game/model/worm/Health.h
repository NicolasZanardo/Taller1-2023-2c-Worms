#ifndef TP_WORMS_HEALTH_H
#define TP_WORMS_HEALTH_H

#include <memory>
#include "../weapons/Damage.h"

class Health {
    float actual_health;
    bool is_alive;


public:
    explicit Health(float initial_health);
    void on_update();
    bool IsAlive();
    bool Amount();

    void receive_damage(Damage& damage);
    bool heal(float amount);

};


#endif //TP_WORMS_HEALTH_H

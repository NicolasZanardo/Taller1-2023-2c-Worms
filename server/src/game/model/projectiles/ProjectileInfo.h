
#ifndef TP_WORMS_PROJECTILE_H
#define TP_WORMS_PROJECTILE_H


#include "../core/Updatable.h"
#include "../weapons/Damage.h"

class Projectile: public Updatable {
public:
    Damage &damage;
    float power;
    float origin_x;
    float origin_y;

    Projectile(Damage &damage, float power, float origin_x, float origin_y);
    void update() override;
};


#endif //TP_WORMS_PROJECTILE_H

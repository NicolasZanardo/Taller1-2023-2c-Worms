#ifndef TP_WORMS_WINDSYSTEM_H
#define TP_WORMS_WINDSYSTEM_H

#include <vector>
#include <memory>
#include "../../model/projectiles/Projectile.h"
#include "../../model/forces/WindForce.h"

class WindSystem {
    float wind_speed;
    WindForce force;
    void init();
public:
    WindSystem(b2World &world);

    void update(
        const std::vector<std::shared_ptr<Projectile>> &projectiles
    );

    float get_wind_speed() const;
};


#endif //TP_WORMS_WINDSYSTEM_H

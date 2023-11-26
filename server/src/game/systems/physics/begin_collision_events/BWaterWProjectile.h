#ifndef TP_WORMS_BWATERWPROJECTILE_H
#define TP_WORMS_BWATERWPROJECTILE_H


#include "../../../model/core/Collidable.h"

class BWaterWProjectile {
public:
    BWaterWProjectile() = default;

    static void resolve(Collidable *water_collideable, Collidable *projectile_collideable);
    static void resolve_inverse(Collidable *water_collideable, Collidable *projectile_collideable);
};


#endif //TP_WORMS_BWATERWPROJECTILE_H

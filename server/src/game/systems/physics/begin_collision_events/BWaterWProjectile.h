#ifndef TP_WORMS_BWATERWPROJECTILE_H
#define TP_WORMS_BWATERWPROJECTILE_H


#include "../../../model/core/Collidable.h"
#include <box2d/box2d.h>

class BWaterWProjectile {
public:
    BWaterWProjectile() = default;

    static void resolve(Collidable *water_collidable, Collidable *projectile_collidable, b2Manifold* manifold);
    static void resolve_inverse(Collidable *water_collidable, Collidable *projectile_collidable, b2Manifold* manifold);
};


#endif //TP_WORMS_BWATERWPROJECTILE_H

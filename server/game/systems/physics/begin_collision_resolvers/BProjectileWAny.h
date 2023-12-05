#ifndef TP_WORMS_BPROJECTILEWANY_H
#define TP_WORMS_BPROJECTILEWANY_H

#include <box2d/box2d.h>
#include "Collidable.h"

class BProjectileWAny {
public:
    BProjectileWAny() = default;

    static void resolve(Collidable *projectile_collidable, Collidable *any, b2Contact* contact);

    static void resolve_inverse(Collidable *any, Collidable *projectile_collidable, b2Contact* contact);
};


#endif //TP_WORMS_BPROJECTILEWANY_H

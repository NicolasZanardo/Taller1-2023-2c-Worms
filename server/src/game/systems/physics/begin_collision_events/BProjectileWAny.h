#ifndef TP_WORMS_BPROJECTILEWANY_H
#define TP_WORMS_BPROJECTILEWANY_H

#include <box2d/box2d.h>
#include "../../../model/core/Collidable.h"

class BProjectileWAny {
public:
    BProjectileWAny() = default;

    static void resolve(Collidable *projectile_collidable, Collidable *any);

    static void resolve_inverse(Collidable *any, Collidable *projectile_collidable);
};


#endif //TP_WORMS_BPROJECTILEWANY_H

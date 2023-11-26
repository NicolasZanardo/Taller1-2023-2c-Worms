#ifndef TP_WORMS_BPROJECTILEWANY_H
#define TP_WORMS_BPROJECTILEWANY_H

#include <box2d/box2d.h>
#include "../../../model/core/Collidable.h"

class BProjectileWAny {
    constexpr static const float explosion_power = 20;

    static void apply_blast_impulse(b2Body *body, b2Vec2 blast_center, b2Vec2 apply_point, float distance);

public:
    BProjectileWAny() = default;

    static void resolve(Collidable *projectile_collideable, Collidable *any);

    static void resolve_inverse(Collidable *any, Collidable *projectile_collideable);
};


#endif //TP_WORMS_BPROJECTILEWANY_H

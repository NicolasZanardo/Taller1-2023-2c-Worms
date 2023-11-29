#ifndef TP_WORMS_ONEXPLOSIONWORMSQUERY_H
#define TP_WORMS_ONEXPLOSIONWORMSQUERY_H

#include <box2d/box2d.h>
#include "Projectile.h"

class OnExplosionWormsQuery {
public:
    static void act_on_found(b2World& world, std::unique_ptr<CExplosion> explosion);
};

#endif //TP_WORMS_ONEXPLOSIONWORMSQUERY_H

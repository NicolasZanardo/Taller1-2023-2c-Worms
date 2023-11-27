#ifndef TP_WORMS_BWATERWWORM_H
#define TP_WORMS_BWATERWWORM_H


#include "../../../model/core/Collidable.h"
#include <box2d/box2d.h>

class BWaterWWorm {
public:
    BWaterWWorm() = default;

    static void resolve(Collidable *water_collidable, Collidable *worm_collidable, b2Manifold* manifold);
    static void resolve_inverse(Collidable *worm_collidable, Collidable *water_collidable, b2Manifold* manifold);
};

#endif //TP_WORMS_BWATERWWORM_H

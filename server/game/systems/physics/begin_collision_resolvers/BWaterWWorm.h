#ifndef TP_WORMS_BWATERWWORM_H
#define TP_WORMS_BWATERWWORM_H


#include "Collidable.h"
#include <box2d/box2d.h>

class BWaterWWorm {
public:
    BWaterWWorm() = default;

    static void resolve(Collidable *water_collidable, Collidable *worm_collidable, b2Contact* contact);
    static void resolve_inverse(Collidable *worm_collidable, Collidable *water_collidable, b2Contact* contact);
};

#endif //TP_WORMS_BWATERWWORM_H

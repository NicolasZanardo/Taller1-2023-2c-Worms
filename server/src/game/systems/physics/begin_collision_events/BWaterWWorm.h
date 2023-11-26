#ifndef TP_WORMS_BWATERWWORM_H
#define TP_WORMS_BWATERWWORM_H


#include "../../../model/core/Collidable.h"

class BWaterWWorm {
public:
    BWaterWWorm() = default;

    static void resolve(Collidable *water_collidable, Collidable *worm_collidable);
    static void resolve_inverse(Collidable *worm_collidable, Collidable *water_collidable);
};

#endif //TP_WORMS_BWATERWWORM_H

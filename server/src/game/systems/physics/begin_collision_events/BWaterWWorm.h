#ifndef TP_WORMS_BWATERWWORM_H
#define TP_WORMS_BWATERWWORM_H


#include "../../../model/core/Collidable.h"

class BWaterWWorm {
public:
    BWaterWWorm() = default;

    static void resolve(Collidable *water_collideable, Collidable *worm_collideable);
    static void resolve_inverse(Collidable *water_collideable, Collidable *worm_collideable);
};

#endif //TP_WORMS_BWATERWWORM_H

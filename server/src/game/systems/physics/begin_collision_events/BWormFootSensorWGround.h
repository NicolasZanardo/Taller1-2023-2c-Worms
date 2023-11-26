#ifndef TP_WORMS_BWORMFOOTSENSORWGROUND_H
#define TP_WORMS_BWORMFOOTSENSORWGROUND_H

#include "../../../model/core/Collidable.h"

class BWormFootSensorWGround {
public:
    explicit BWormFootSensorWGround() = default;
    static void resolve(Collidable *worm_collideable, Collidable *ground_collideable);
    static void resolve_inverse(Collidable *worm_collideable, Collidable *ground_collideable);
};

#endif //TP_WORMS_BWORMFOOTSENSORWGROUND_H

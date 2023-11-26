#ifndef TP_WORMS_BWORMFOOTSENSORWGROUND_H
#define TP_WORMS_BWORMFOOTSENSORWGROUND_H

#include "../../../model/core/Collidable.h"

class BWormFootSensorWGround {
public:
    explicit BWormFootSensorWGround() = default;
    static void resolve(Collidable *sensor_collidable, Collidable *ground_collidable);
    static void resolve_inverse(Collidable *ground_collidable, Collidable *sensor_collidable);
};

#endif //TP_WORMS_BWORMFOOTSENSORWGROUND_H

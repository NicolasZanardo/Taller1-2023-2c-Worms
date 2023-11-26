#ifndef TP_WORMS_EWORMFOOTSENSORWGROUND_H
#define TP_WORMS_EWORMFOOTSENSORWGROUND_H

#include "../../../model/core/Collidable.h"

class EWormFootSensorWGround {
public:
    EWormFootSensorWGround() = default;
    static void resolve(Collidable *worm_foot_sensor_collideable, Collidable *ground_collideable);
    static void resolve_inverse(Collidable *ground_collideable, Collidable *worm_foot_sensor_collideable);
};


#endif //TP_WORMS_EWORMFOOTSENSORWGROUND_H

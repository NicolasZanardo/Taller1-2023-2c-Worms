#ifndef TP_WORMS_EWORMFOOTSENSORWGROUND_H
#define TP_WORMS_EWORMFOOTSENSORWGROUND_H

#include "../../../model/core/Collidable.h"
#include <box2d/box2d.h>

class EWormFootSensorWGround {
public:
    EWormFootSensorWGround() = default;
    static void resolve(Collidable *worm_foot_sensor_collidable, Collidable *ground_collidable, b2Contact* contact);
    static void resolve_inverse(Collidable *ground_collidable, Collidable *worm_foot_sensor_collidable, b2Contact* contact);
};


#endif //TP_WORMS_EWORMFOOTSENSORWGROUND_H

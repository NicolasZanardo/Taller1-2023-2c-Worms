#ifndef TP_WORMS_BWORMFOOTSENSORWGROUND_H
#define TP_WORMS_BWORMFOOTSENSORWGROUND_H

#include "../../../model/core/Collidable.h"
#include <box2d/box2d.h>

class BWormFootSensorWGround {
public:
    explicit BWormFootSensorWGround() = default;
    static void resolve(Collidable *sensor_collidable, Collidable *ground_collidable, b2Contact* contact);
    static void resolve_inverse(Collidable *ground_collidable, Collidable *sensor_collidable, b2Contact* contact);
};

#endif //TP_WORMS_BWORMFOOTSENSORWGROUND_H


#include "BWormFootSensorWGround.h"
#include "../../../model/worm/Worm.h"
#include "../../../model/worm/WormFootSensor.h"
#include <iostream>

void BWormFootSensorWGround::resolve(Collidable *sensor_collidable, Collidable *ground_collidable, b2Manifold* manifold) {
    auto sensor = dynamic_cast<WormFootSensor*>(sensor_collidable);
    if (sensor) {
        sensor->sense_ground_contact();
    }
}

void BWormFootSensorWGround::resolve_inverse(Collidable *ground_collidable, Collidable *sensor_collidable, b2Manifold* manifold) {
    resolve(sensor_collidable, ground_collidable, manifold);
}

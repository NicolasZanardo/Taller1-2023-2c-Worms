
#include "BWormFootSensorWGround.h"
#include "../../../model/worm/Worm.h"
#include "../../../model/worm/WormFootSensor.h"
#include <iostream>

void BWormFootSensorWGround::resolve(Collidable *worm_foot_sensor_collideable, Collidable *ground_collideable) {
    auto sensor = dynamic_cast<WormFootSensor*>(worm_foot_sensor_collideable);
    if (sensor) {
        sensor->sense_ground_contact();
    }
}

void BWormFootSensorWGround::resolve_inverse(Collidable *ground_go, Collidable *worm_go) {
    resolve(worm_go, ground_go);
}

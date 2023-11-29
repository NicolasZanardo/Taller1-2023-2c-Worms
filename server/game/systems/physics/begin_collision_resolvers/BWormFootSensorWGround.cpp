
#include "BWormFootSensorWGround.h"
#include "Worm.h"
#include "WormFootSensor.h"
#include <iostream>

void BWormFootSensorWGround::resolve(Collidable *sensor_collidable, Collidable *ground_collidable, b2Contact* contact) {
    auto sensor = dynamic_cast<WormFootSensor*>(sensor_collidable);
    if (sensor) {
        sensor->sense_ground_contact();
    }
}

void BWormFootSensorWGround::resolve_inverse(Collidable *ground_collidable, Collidable *sensor_collidable, b2Contact* contact) {
    resolve(sensor_collidable, ground_collidable, contact);
}

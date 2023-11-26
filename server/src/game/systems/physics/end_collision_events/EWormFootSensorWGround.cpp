#include "EWormFootSensorWGround.h"
#include "../../../model/worm/Worm.h"
#include "../../../model/worm/WormFootSensor.h"

void EWormFootSensorWGround::resolve(Collidable *worm_foot_sensor_collideable, Collidable *ground_collideable) {
    auto sensor = dynamic_cast<WormFootSensor*>(worm_foot_sensor_collideable);
    if (sensor) {
        sensor->sense_ground_contact_ended();
    }
}

void
EWormFootSensorWGround::resolve_inverse(Collidable *ground_collideable, Collidable *worm_foot_sensor_collideable) {
    resolve(worm_foot_sensor_collideable, ground_collideable);
}

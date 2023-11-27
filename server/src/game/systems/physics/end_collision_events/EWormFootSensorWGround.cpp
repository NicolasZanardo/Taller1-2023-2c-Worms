#include "EWormFootSensorWGround.h"
#include "../../../model/worm/Worm.h"
#include "../../../model/worm/WormFootSensor.h"

void EWormFootSensorWGround::resolve(Collidable *worm_foot_sensor_collidable, Collidable *ground_collidable, b2Contact* contact) {
    auto sensor = dynamic_cast<WormFootSensor*>(worm_foot_sensor_collidable);
    if (sensor) {
        sensor->sense_ground_contact_ended();
    }
}

void
EWormFootSensorWGround::resolve_inverse(Collidable *ground_collidable, Collidable *worm_foot_sensor_collidable, b2Contact* contact) {
    resolve(worm_foot_sensor_collidable, ground_collidable, contact);
}

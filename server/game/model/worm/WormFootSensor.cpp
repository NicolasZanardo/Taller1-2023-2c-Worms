#include "WormFootSensor.h"
#include "CollideableTags.h"
#include "Worm.h"

WormFootSensor::WormFootSensor(Worm *worm): Collidable(WORM_FOOT_SENSOR_TAG), worm(worm) {}

void WormFootSensor::sense_ground_contact() const {
    worm->on_sensed_one_new_ground_contact();
}

void WormFootSensor::sense_ground_contact_ended() const {
    worm->on_sensed_one_ground_contact_ended();
}

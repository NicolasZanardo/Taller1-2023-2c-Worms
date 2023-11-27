#include "WindForce.h"

WindForce::WindForce(b2World &world, float wind_speed): Force(world), wind_speed(wind_speed) {}

void WindForce::apply(b2Body *body) {
    float forceMagnitude = wind_speed * body->GetMass();
    b2Vec2 wind_force(forceMagnitude, 0.0f);
    body->ApplyForce(wind_force, body->GetWorldCenter(), true);
}

void WindForce::on_wind_change(float new_wind_speed) {
    wind_speed = new_wind_speed;
}
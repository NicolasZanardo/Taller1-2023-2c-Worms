#include "Body.h"
#include <stdexcept>

Body::Body(b2World &world, b2Body *body, bool is_facing_right) :
    world(world), body(body), is_facing_right(is_facing_right) {}

Body::~Body() {
    if (body) {
        world.DestroyBody(body);
        body = nullptr;
    }
}

float Body::X() const {
    return body->GetPosition().x;
}

float Body::Y() const {
    return body->GetPosition().y;
}

float Body::Angle() const {
    return body->GetPosition().y;
}
b2Body *Body::B2Body() {
    return body;
}

void Body::receive(Force &force) {
    force.apply(body);
}

bool Body::is_moving_faster_than(const std::shared_ptr<Body> &other) {
    b2Vec2 velocity1 = body->GetLinearVelocity();
    b2Vec2 velocity2 = other->body->GetLinearVelocity();

    float speed1 = velocity1.Length();
    float speed2 = velocity2.Length();

    return speed1 > speed2;
}


bool Body::facing_right() const {
    return is_facing_right;
}


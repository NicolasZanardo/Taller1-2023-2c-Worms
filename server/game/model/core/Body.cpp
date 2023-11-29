#include "Body.h"
#include <stdexcept>

Body::Body(b2World &world, b2Body *body) : world(world), body(body) {}

Body::~Body() {
    if (body) {
        world.DestroyBody(body);
        body = nullptr;
    }
}

float Body::X() const {
    if (body == nullptr) {
        throw std::runtime_error("Attempted to access X() on a detached body.");
    }
    return body->GetPosition().x;
}

float Body::Y() const {
    if (body == nullptr) {
        throw std::runtime_error("Attempted to access Y() on a detached body.");
    }
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


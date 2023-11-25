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

#include "Body.h"
#include <cmath>
#include <iostream>
const float EPSILON = 0.005;
const float RAD_TO_DEG = 180.0f / M_PI;

Body::Body(b2World &world, b2Body *body, bool is_facing_right) :
    world(world), body(body), is_facing_right(is_facing_right) {}

Body::Body(Body&& other) noexcept
    : world(other.world), body(other.body), is_facing_right(other.is_facing_right) {
    other.body = nullptr;
}

Body::~Body() {
    std::cout << "Entered ~Body" << std::endl;
    if (body) {
        std::cout << "body is not null" << std::endl;
        world.DestroyBody(body);
        std::cout << "Destroyed body with world on ~Body\n";
        body = nullptr;
    }
}

float Body::X() const {
    return body->GetPosition().x;
}

float Body::Y() const {
    return body->GetPosition().y;
}

bool Body::is_still() const {
    return std::abs(body->GetLinearVelocity().x) < EPSILON &&
        std::abs(body->GetLinearVelocity().y) < EPSILON;
}


float Body::AngleInDeg() const {
    return body->GetAngle() * RAD_TO_DEG;
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


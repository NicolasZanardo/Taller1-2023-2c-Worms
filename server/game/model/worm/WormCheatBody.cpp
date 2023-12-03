#include "WormCheatBody.h"
#include "Worm.h"
#include <iostream>

WormCheatBody::WormCheatBody(b2World &world, b2Body *body, WormCfg &worm_cfg) :
    WormBodyComponent(world, body, worm_cfg) {};

WormCheatBody::WormCheatBody(std::shared_ptr<WormBodyComponent> &&other) : WormBodyComponent(std::move(other)) {}

void WormCheatBody::update(const std::shared_ptr<Worm> &worm) {
    float y_velocity = body->GetLinearVelocity().y;

    if (is_moving) {
        body->SetLinearVelocity((b2Vec2(facing_direction_sign() * speed, y_velocity)));
    } else if (is_jumping) {
        worm->state = WormStateDto::JUMPING;
    } else if (y_velocity < -epsilon_y) {
        worm->state = WormStateDto::FALLING;
    } else {
        if (abs(body->GetLinearVelocity().x) < epsilon_y) {
            worm->state = WormStateDto::IDLE;
        } else {
            worm->state = WormStateDto::MOVING;
        }
    }
}

void WormCheatBody::on_sensed_one_new_ground_contact() {
    ground_contact_count++;
    is_on_ground = (ground_contact_count > 0);
    is_jumping = false;
}

void WormCheatBody::on_sensed_one_ground_contact_ended() {
    ground_contact_count--;
    is_on_ground = (ground_contact_count > 0);
}


char WormCheatBody::facing_direction_sign() const {
    if (is_facing_right) {
        return 1;
    } else {
        return -1;
    }
}

void WormCheatBody::start_moving_right() {
    std::cout << "Entered here\n";
    is_facing_right = true;
    is_moving = true;
}

void WormCheatBody::start_moving_left() {
    is_facing_right = false;
    is_moving = true;
}

void WormCheatBody::stop_moving() { //left right
    is_moving = false;
    b2Vec2 velocity = body->GetLinearVelocity();
    velocity.x = 0.0f;
    body->SetLinearVelocity(velocity);
}

void WormCheatBody::jump_forward() {
    std::cout << "Entered here\n";
    is_jumping = true;
    body->SetLinearVelocity(b2Vec2(0, 0));
    body->ApplyLinearImpulseToCenter(
        b2Vec2(
            facing_direction_sign() * forward_jump_reach * body->GetMass(),
            forward_jump_height * body->GetMass()
        ), true);
}

void WormCheatBody::jump_backwards() {
    std::cout << "Entered here\n";
    is_jumping = true;
    body->SetLinearVelocity(b2Vec2(0, 0));
    body->ApplyLinearImpulseToCenter(
        b2Vec2(
            (-facing_direction_sign()) * backwards_jump_reach * body->GetMass(),
            backwards_jump_height * body->GetMass()
        ),
        true);
}

void WormCheatBody::sink() {}

void WormCheatBody::on_turn_ended() { is_moving = false; }

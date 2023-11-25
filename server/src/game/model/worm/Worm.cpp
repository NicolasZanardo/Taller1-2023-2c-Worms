#include "Worm.h"
#include "../weapons/Bazooka.h"
#include "../weapons/Mortar.h"
#include "../weapons/GreenGrenade.h"
#include "../../core/Logger.h"
#include <iostream>

Worm::Worm(size_t id) :
    Instance(id),
    weapons(create_default_weapons()),
    actual_weapon(weapons[WeaponTypeDto::BAZOOKA]),
    health(100),
    body(nullptr),
    has_done_an_ending_turn_action(false) {}

WormDto Worm::toWormDto(size_t client_id) {
    return WormDto(
        client_id,
        id,
        X(),
        Y(),
        0,
        body->facing_right(),
        health.Amount(),
        body->state_to_dto(),
        actual_weapon->WeaponType(),
        actual_weapon->AimedAngle()
    );
}

WeaponMap Worm::create_default_weapons() {
    WeaponMap default_weapons;

    // Damages inside weapons could later be only created one for each weapon kind and just have a reference
    // In order to not have multiple same damage object
    default_weapons[WeaponTypeDto::BAZOOKA] = std::make_unique<Bazooka>(id, 10, 50, 2);
    default_weapons[WeaponTypeDto::MORTAR] = std::make_unique<Mortar>(id, 10, 50, 2);
    default_weapons[WeaponTypeDto::GREEN_GRENADE] = std::make_unique<GreenGrenade>(id, 10, 70, 4);

    return default_weapons;
}

float Worm::X() const {
    return body->X();
}

float Worm::Y() const {
    return body->Y();
}

b2Body* Worm::B2Body() const {
    return body->B2Body();
}

void Worm::update(const int it) {
    health.on_update();
    if (!health.IsAlive()) {
        std::cout << "Worm id: " << id << "died\n";
        is_active = false;
        return;
    }

    body->on_update();
    if (actual_weapon) {
        actual_weapon->on_update();
    }
}

void Worm::on_turn_ended() {
    body->on_turn_ended();
    if (actual_weapon) {
        actual_weapon->on_turn_ended();
    }
    has_done_an_ending_turn_action = false;
}


// Movement
void Worm::start_moving_right() const {
    body->start_moving_right();
}

void Worm::start_moving_left() const {
    body->start_moving_left();
}

void Worm::stop_moving() const {
    body->stop_moving();
}

void Worm::jump_forward() const {
    body->jump_forward();
}

void Worm::jump_backwards() const {
    body->jump_backwards();
}

void Worm::start_aiming_down() {
    if (actual_weapon) {
        actual_weapon->start_aiming_down();
    }
}

void Worm::start_aiming_up() {
    if (actual_weapon) {
        actual_weapon->start_aiming_up();
    }

}

void Worm::stop_aiming_up() {
    if (actual_weapon) {
        actual_weapon->stop_aiming_up();
    }
}

void Worm::stop_aiming_down() {
    if (actual_weapon) {
        actual_weapon->stop_aiming_down();
    }
}

void Worm::start_shooting() {
    if (actual_weapon) {
        // Logger::log_position("Worm shot", X(), Y());
        actual_weapon->start_shooting(X(),Y(),body->facing_direction_sign());
    }
}

void Worm::end_shooting() {
    if (actual_weapon) {
        actual_weapon->end_shooting(X(),Y(),body->facing_direction_sign());
    }
}

void Worm::change_weapon(WeaponTypeDto weapon) {
    actual_weapon = weapons[weapon]; // We know weapons from the start
}

// At this call the shot is instantiated, so here is when the worm does an ending turn action
// Depending on the weapon could be in start_shooting, when the max power charges or in end_shooting
std::unique_ptr<CShot> Worm::shot_component() {
    auto c_shot = actual_weapon->shot_component();
    if (c_shot) {
        has_done_an_ending_turn_action = true;
    }
    return c_shot;
}

void Worm::heal(float amount) {
    health.heal(amount);
}

void Worm::receive_damage(float damage) {
    std::cout << "Worm id: " << id << " received: " << damage << " damage\n";
    health.receive_damage(damage);
}


#include "Worm.h"
#include "../weapons/Bazooka.h"
#include "../weapons/Morter.h"
#include "../weapons/GreenGrenade.h"
#include <iostream>

Worm::Worm(size_t id) :
    Instance(id),
    weapons(create_default_weapons()),
    actual_weapon(weapons[WeaponTypeDto::BAZOOKA]),
    movement(nullptr),
    has_done_an_ending_turn_action(false) {}

WormDto Worm::toWormDto(size_t client_id) {
    return WormDto(
        client_id,
        id,
        movement->x(),
        movement->y(),
        0,
        movement->facing_right(),
        health,
        movement->state_to_dto()
    );
}

WeaponMap Worm::create_default_weapons() {
    WeaponMap default_weapons;

    default_weapons[WeaponTypeDto::BAZOOKA] = std::make_unique<Bazooka>(10, Damage(50, 2));
    default_weapons[WeaponTypeDto::MORTER] = std::make_unique<Morter>(10, Damage(50, 2));
    default_weapons[WeaponTypeDto::GREEN_GRENADE] = std::make_unique<GreenGrenade>(10, Damage(30, 2));

    return default_weapons;
}

float Worm::X() const {
    return movement->x();
}

float Worm::Y() const {
    return movement->y();
}

void Worm::update() {
    movement->on_update();
    if (actual_weapon) {
        actual_weapon->on_update();
    }
}

void Worm::on_turn_ended() {
    movement->on_turn_ended();
    if (actual_weapon) {
        actual_weapon->on_turn_ended();
    }
    has_done_an_ending_turn_action = false;
}


// Movement
void Worm::start_moving_right() const {
    movement->start_moving_right();
}

void Worm::start_moving_left() const {
    movement->start_moving_left();
}

void Worm::stop_moving() const {
    movement->stop_moving();
}

void Worm::jump_forward() const {
    movement->jump_forward();
}

void Worm::jump_backwards() const {
    movement->jump_backwards();
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
        actual_weapon->start_shooting(X(), Y());
    }
}

void Worm::end_shooting() {
    if (actual_weapon) {
        actual_weapon->end_shooting(X(), Y());
    }
}

void Worm::change_weapon(WeaponTypeDto weapon) {
    actual_weapon = weapons[weapon];
    std::cout << "Changed weapon" << std::endl;
}

// At this call the shot is instantiated, so here is when the worm does an ending turn action
// Depending on the weapon could be in start_shooting or in end_shooting
std::unique_ptr<Shot> Worm::shot_component() {
    auto c_shot = actual_weapon->shot_component();
    if (c_shot) {
        has_done_an_ending_turn_action = true;
    }
    return c_shot;
}




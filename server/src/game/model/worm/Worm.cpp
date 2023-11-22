#include "Worm.h"
#include <iostream>
#include <utility>

Worm::Worm(size_t id, WeaponMap weapons) :
        Instance(id),
        weapons(std::move(weapons)),
        actual_weapon(nullptr),
        movement(nullptr) {}

Worm::Worm(size_t id) : // TODO FOR NOW WITHOUT WEAPONS
        Instance(id),
        weapons(),
        actual_weapon(new Weapon()), // TODO Start with nullptr then
        movement(nullptr) {}

WormDto Worm::toWormDto(size_t clientId) {
    return WormDto(
            clientId,
            id,
            movement->x(),
            movement->y(),
            0,
            movement->facing_right(),
            health,
            movement->state_to_dto()
    );
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
    // TODO change actual_weapon to nullptr
}

// Movement
void Worm::start_moving_right() {
    movement->start_moving_right();
}

void Worm::start_moving_left() {
    movement->start_moving_left();
}

void Worm::stop_moving() {
    movement->stop_moving();
}

void Worm::jump_forward() {
    movement->jump_forward();
}

void Worm::jump_backwards() {
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



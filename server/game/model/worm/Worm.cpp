#include <utility>
#include "Worm.h"
#include "CollideableTags.h"
#include "WeaponFactory.h"
#include "CheatType.h"
#include "GameAction.h"
#include <iostream>

Worm::Worm(
    size_t id,
    WormCfg &worm_cfg,
    std::shared_ptr<WeaponsComponent> weapons_component
) :
    Collidable(WORM_TAG),
    Instance(id),
    state(WormStateDto::IDLE),
    weapons_component(std::move(weapons_component)),
    health(worm_cfg.health.default_health),
    foot_sensor(this),
    is_on_water(false),
    water_death_timer(WATER_DEATH_TIME),
    finished_turn(false),
    body(nullptr)
    {}

WormDto Worm::toWormDto(size_t client_id) {
    return WormDto(
        client_id,
        id,
        X(),
        Y(),
        0,
        body->facing_right(),
        health.amount(),
        state,
        weapons_component->WeaponType(),
        weapons_component->AimedAngle()
    );
}

void Worm::update(const int it, const int rate) {
    if (!health.update(shared_from_this(), it, rate)) {
        state = WormStateDto::DEAD;
        return;
    }
    body->update(shared_from_this());
    weapons_component->update(it, rate);
}

float Worm::X() const {
    return body->X();
}

float Worm::Y() const {
    return body->Y();
}

bool Worm::is_still() const {
    return body->is_still();
}

b2Body *Worm::B2Body() const {
    return body->B2Body();
}

void Worm::receive_force(Force& force) {
    body->receive(force);
}

std::shared_ptr<WormBody> Worm::get_body() const {
    return body;
}

WormFootSensor *Worm::get_foot_sensor() {
    return &foot_sensor;
}

// Turn
void Worm::on_turn_ended() {
    body->on_turn_ended();
    weapons_component->on_turn_ended();
    finished_turn = false;
}

bool Worm::has_done_ending_turn_action() const {
    return finished_turn;
}

// Movement
void Worm::on_sensed_one_new_ground_contact() const {
    body->on_sensed_one_new_ground_contact();
}

void Worm::on_sensed_one_ground_contact_ended() const {
    body->on_sensed_one_ground_contact_ended();
}

void Worm::sink() {
    is_on_water = true;
    body->sink();
}

// At this call the shot is instantiated, so here is when the worm does an ending turn action
// Depending on the weapon could be in start_shooting, when the max power charges or in end_shooting
std::unique_ptr<CShot> Worm::shot_component() {
    auto c_shot = weapons_component->shot_component();
    if (c_shot) {
        finished_turn = true;
    }
    return c_shot;
}

// Actions

void Worm::act(GameAction action) {
    switch (action) {
        case GameAction::RESERVED:
            break;
        case GameAction::MOVE_LEFT_INIT:
            body->start_moving_left();
            break;
        case GameAction::MOVE_LEFT_END:
            body->stop_moving();
            break;
        case GameAction::MOVE_RIGHT_INIT:
            body->start_moving_right();
            break;
        case GameAction::MOVE_RIGHT_END:
            body->stop_moving();
            break;
        case GameAction::JUMP_FORWARD:
            body->jump_forward();
            break;
        case GameAction::JUMP_BACKWARDS:
            body->jump_backwards();
            break;
        case GameAction::AIM_UP_INIT:
            if (!has_done_an_ending_turn_action)
                weapons_component->start_aiming_up();
            break;
        case GameAction::AIM_DOWN_INIT:
            if (!has_done_an_ending_turn_action)
                weapons_component->start_aiming_down();
            break;
        case GameAction::AIM_UP_STOPPED:
            weapons_component->stop_aiming_up();
            break;
        case GameAction::AIM_DOWN_STOPPED:
            if (!has_done_an_ending_turn_action)
                weapons_component->stop_aiming_down();
            break;
        case GameAction::WEAPON_PRIMARY_ACTION:
            if (!has_done_an_ending_turn_action)
                weapons_component->do_weapon_primary_action(X(), Y(), body->facing_direction_sign());
            break;
        case GameAction::WEAPON_SECONDARY_ACTION:
            if (!has_done_an_ending_turn_action)
                weapons_component->do_weapon_secondary_action(X(), Y(), body->facing_direction_sign());
            break;
    }

}

// Health
void Worm::adjust_health_to(float amount) {
    health.adjust_health_to(amount);
}

void Worm::receive_damage(float damage) {
    if (health.receive_damage(damage))
        state = WormStateDto::DEAD;
}

// Weapons
void Worm::change_weapon(WeaponTypeDto weapon) {
    if (weapons_component) {
        weapons_component->change_weapon(weapon);
    }
}

void Worm::change_projectile_count_down(ProjectileCountDown time) {
    if (weapons_component) {
        weapons_component->change_projectile_count_down(time);
    }
}

// Cheat
void Worm::toggle_cheat_mode(CheatType type) {
    cheat_manager.toggle_cheat(type, shared_from_this());
}

void Worm::cheat_movement(bool toggled) {
    /*if (toggled) {
        body = std::make_shared<WormCheatBody>(std::move(body));
    } else {
        body = std::make_shared<WormBody>(std::move(body));
    }*/
}

void Worm::cheat_health() {
    health.toggle_cheat_mode();
}

void Worm::cheat_weapon(int new_ammo, float new_damage) {
    weapons_component->upgrade_actual_weapon(new_ammo, new_damage);
}

#include "Worm.h"
#include "CollideableTags.h"
#include "WeaponFactory.h"
#include <iostream>

Worm::Worm(size_t id, WormCfg &worm_cfg, Config<WeaponCfg>& weapons_cfg) :
    Collidable(WORM_TAG),
    Instance(id),
    is_dead(false),
    weapons(create_default_weapons(weapons_cfg)),
    actual_weapon(weapons[WeaponTypeDto::BAZOOKA]),
    health(worm_cfg.health.default_health),
    foot_sensor(this),
    is_on_water(false),
    water_death_timer(WATER_DEATH_TIME),
    finished_turn(false),
    body(nullptr)
    {}

WormDto Worm::toWormDto(size_t client_id) {
    MovementStateDto state;
    if (health.IsAlive()) {
        state = body->state_to_dto();
    } else {
        state = MovementStateDto::DEAD; // TODO For simplicity is in movementState
    }

    return WormDto(
        client_id,
        id,
        X(),
        Y(),
        0,
        body->facing_right(),
        health.Amount(),
        state,
        actual_weapon->WeaponType(),
        actual_weapon->AimedAngle()
    );
}

WeaponMap Worm::create_default_weapons(Config<WeaponCfg> &weapons_cfg) {
    WeaponMap default_weapons;
    for (auto [cfg_id, weapon_cfg]: weapons_cfg) {
        default_weapons[weapon_cfg.type] = WeaponFactory::create(weapon_cfg);
    }
    return default_weapons;
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

bool Worm::is_alive() const {
    return !is_dead;
}

b2Body* Worm::B2Body() const {
    return body->B2Body();
}

WormFootSensor* Worm::get_foot_sensor() {
    return &foot_sensor;
}


void Worm::update(const int it, const int rate) {
    if (is_dead) {
        is_active = false;
    }
    if (is_on_water) {
        water_death_timer -= it * rate;
        if (water_death_timer <= 0) {
            // std::cout << "Worm id: " << id << "died\n";
            health.die();
            is_dead = true;
            return;
        }
    }

    health.on_update();
    if (!health.IsAlive()) {
        // std::cout << "Worm id: " << id << "died\n";
        is_dead = true;
        return;
    }

    body->on_update();
    if (actual_weapon) {
        actual_weapon->on_update(it, rate);
    }
}


// Turn

void Worm::on_turn_ended() {
    body->on_turn_ended();
    if (actual_weapon) {
        actual_weapon->on_turn_ended();
        actual_weapon = weapons[WeaponTypeDto::BAZOOKA];
    }
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

void Worm::sink() {
    is_on_water = true;
    body->sink();
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
    if (actual_weapon && !finished_turn) {
        actual_weapon->start_shooting(X(),Y(),body->facing_direction_sign());
    }
}

void Worm::end_shooting() {
    if (actual_weapon && !finished_turn) {
        actual_weapon->end_shooting(X(),Y(),body->facing_direction_sign());
    }
}

void Worm::change_weapon(WeaponTypeDto weapon) {
    actual_weapon = weapons[weapon];
}

void Worm::change_projectile_count_down(ProjectileCountDown count_down) {
    if (actual_weapon) {
        actual_weapon->change_projectile_count_down(count_down);
    }
}

// At this call the shot is instantiated, so here is when the worm does an ending turn action
// Depending on the weapon could be in start_shooting, when the max power charges or in end_shooting
std::unique_ptr<CShot> Worm::shot_component() {
    auto c_shot = actual_weapon->shot_component();
    if (c_shot) {
        finished_turn = true;
    }
    return c_shot;
}

// Health
void Worm::adjust_health_to(float amount) {
    health.adjust_health_to(amount);
}

void Worm::receive_damage(float damage) {
    std::cout << "Worm id: " << id << " received: " << damage << " damage\n";
    health.receive_damage(damage);
}


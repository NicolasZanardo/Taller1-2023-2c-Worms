#include "WindSystem.h"
#include <random>

WindSystem::WindSystem(b2World &world): wind_speed(0), force(world, wind_speed) {
    init();
}

void WindSystem::update(const std::vector<std::shared_ptr<Projectile>> &projectiles) {
    for (const auto &projectile : projectiles) {
        projectile->receive(force);
    }
}

float WindSystem::get_wind_speed() const {
    return wind_speed;
}

void WindSystem::init() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.2f, 10.0f);
    bool left_direction = std::uniform_int_distribution<int>(0, 1)(gen) == 0;
    wind_speed = dist(gen);
    if (left_direction) {
        wind_speed *= -1;
    }
    force.on_wind_change(wind_speed);
}

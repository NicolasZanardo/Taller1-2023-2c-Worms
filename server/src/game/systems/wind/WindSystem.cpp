#include "WindSystem.h"
#include <random>

WindSystem::WindSystem(b2World &world): force(world, 0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.2f, 10.0f);
    wind_speed = dist(gen);
    force.on_wind_change(wind_speed);
}

void WindSystem::update(const std::vector<std::shared_ptr<Projectile>> &projectiles) {
    for (const auto &projectile : projectiles) {
        projectile->receive(force);
    }
}

float WindSystem::get_wind_speed() {
    return wind_speed;
}

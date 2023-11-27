#include <iostream>
#include "CountdownProjectile.h"

CountdownProjectile::CountdownProjectile(
    size_t id,
    const std::unique_ptr<ProjectileInfo> &info
) : Projectile(id, info), countdown_timer(info->countdown) {}

void CountdownProjectile::update(int it, int rate) {
    Projectile::update(it, rate);
    countdown_timer -= it * rate;
    std::cout << "countdown: " << countdown_timer << " ammo left\n";
    if (countdown_timer <= 0) {
        explode();
    }
}

void CountdownProjectile::on_collision(b2Vec2 collision_point) {}

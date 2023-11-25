#include "Projectile.h"

Projectile::Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info) :
    Instance(id),
    weapon_type(info->from_weapon),
    exploded(false),
    damage(info->damage),
    body(nullptr) {}

ProjectileDto Projectile::to_dto() const {
    return ProjectileDto(
        id,
        weapon_type,
        body->X(),
        body->Y()
    );
}

void Projectile::update() {}

void Projectile::explode() {
    exploded = true;
    // TODO Check what happens when
    is_active = false;
}

bool Projectile::has_exploded() {
    return exploded;
}

void Projectile::on_collision() {
    explode(); // TODO Projectile polymorphism, grenades dont explode on collision
}

b2Body* Projectile::B2Body() {
    return body->B2Body();
}

float Projectile::ExplosionRadius() {
    return damage.Radius();
}

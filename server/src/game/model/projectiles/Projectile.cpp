#include "Projectile.h"
#include "../../core/CollideableTags.h"

Projectile::Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info) :
    Collidable(PROJECTILE_TAG),
    Instance(id),
    weapon_type(info->from_weapon),
    exploded(false),
    damage(info->damage),
    explosion_radius(info->explosion_radius),
    body(nullptr)
    {}

ProjectileDto Projectile::to_dto() const {
    return ProjectileDto(
        id,
        weapon_type,
        body->X(),
        body->Y()
    );
}

void Projectile::update(const int it) {
    body->on_update();
}

void Projectile::explode() {
    exploded = true;
    is_active = false;
}

bool Projectile::has_exploded() const {
    return exploded;
}

void Projectile::on_collision() {
    explode(); // TODO Projectile polymorphism, grenades dont explode on collision
}

b2Body* Projectile::B2Body() {
    return body->B2Body();
}

void Projectile::sink() {
    body->sink();
}


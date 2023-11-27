#include "Projectile.h"
#include "../../core/CollideableTags.h"

Projectile::Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info) :
    Collidable(PROJECTILE_TAG),
    Instance(id),
    weapon_type(info->from_weapon),
    exploded(false),
    is_on_water(false),
    on_water_time_life(2000),
    wind_affected(info->affected_by_wind),
    max_damage(info->max_damage),
    explosion_radius(info->explosion_radius),
    body(nullptr) {}

ProjectileDto Projectile::to_dto() const {
    return ProjectileDto(
        id,
        weapon_type,
        body->X(),
        body->Y()
    );
}

b2Body *Projectile::B2Body() const {
    return body->B2Body();
}

float Projectile::X() const {
    return body->X();
}

float Projectile::Y() const {
    return body->Y();
}

void Projectile::receive(Force &force) const {
    if (wind_affected) { // TODO For now the only force the projectile receives is the wind one
        body->receive(force); // TODO if needed can use a ForceReceiverStrategy
    }
}

void Projectile::update(const int it, const int rate) {
    if (is_on_water) {
        on_water_time_life -= it * rate;
        if (on_water_time_life <= 0) {
            is_active = false;
            return;
        }
    }
    body->on_update();
}

void Projectile::explode(float x, float y) {
    exploded = true;
    c_explosion = std::make_unique<CExplosion>(
        max_damage,
        explosion_radius,
        x,
        y
    );
}

bool Projectile::has_exploded() const {
    return exploded;
}

bool Projectile::is_wind_affected() const {
    return wind_affected;
}

void Projectile::sink() {
    is_on_water = true;
    body->sink();
}

std::unique_ptr<CExplosion> Projectile::explosion_component() {
    return std::move(c_explosion);
}


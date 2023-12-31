#include "Projectile.h"
#include "CollideableTags.h"

Projectile::Projectile(size_t id, const std::unique_ptr<ProjectileInfo> &info) :
    Collidable(PROJECTILE_TAG),
    Instance(id),
    type(info->projectile_type),
    exploded(false),
    is_on_water(false),
    on_water_time_life(WATER_LIFE_TIME),
    wind_affected(info->affected_by_wind),
    max_damage(info->max_damage),
    explosion_radius(info->explosion_radius),
    c_explosion(nullptr),
    c_fragments(info->fragment_info ? std::make_unique<CFragments>(std::move(info->fragment_info)) : nullptr),
    body(nullptr) {}

Projectile::Projectile(size_t id, const std::unique_ptr<FragmentsInfo> &info) :
    Collidable(PROJECTILE_TAG),
    Instance(id),
    type(info->projectile_type),
    exploded(false),
    is_on_water(false),
    on_water_time_life(WATER_LIFE_TIME),
    wind_affected(false),
    max_damage(info->max_damage),
    explosion_radius(info->explosion_radius),
    c_explosion(nullptr),
    c_fragments(nullptr),
    body(nullptr) {}

ProjectileDto Projectile::to_dto() const {
    return {
        id,
        type,
        body->X(),
        body->Y(),
        body->did_spawned_facing_right(),
        body->AngleInDeg()
    };
}

ProjectileTypeDto Projectile::get_type() {
    return type;
}

float Projectile::X() const {
    return body->X();
}

float Projectile::Y() const {
    return body->Y();
}

void Projectile::receive(Force &force) const {
    if (wind_affected) { // TODO For now the only force the projectile receives with this method is the wind one
        body->receive(force);
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

void Projectile::sink() {
    is_on_water = true;
    body->sink();
}

std::unique_ptr<CExplosion> Projectile::explosion_component() {
    return std::move(c_explosion);
}

std::unique_ptr<CFragments> Projectile::fragments_component() {
    return std::move(c_fragments);
}


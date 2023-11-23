#include "Projectile.h"

Projectile::Projectile(size_t id, WeaponTypeDto weapon_type): Instance(id), weapon_type(weapon_type), movement(nullptr) {}

ProjectileDto Projectile::to_dto() const {
    return ProjectileDto(
            id,
            weapon_type,
            movement->X(),
            movement->Y()
        );
}

void Projectile::update() {}
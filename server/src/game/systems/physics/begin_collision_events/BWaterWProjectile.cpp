
#include "BWaterWProjectile.h"
#include "../../../model/projectiles/Projectile.h"

void BWaterWProjectile::resolve(Collidable *water_collidable, Collidable *projectile_collidable) {
    auto projec = dynamic_cast<Projectile*>(projectile_collidable);
    if (projec) {
        projec->sink();
    }
}

void BWaterWProjectile::resolve_inverse(Collidable *projectile_collidable, Collidable *water_collidable) {
    resolve(water_collidable, projectile_collidable);
}

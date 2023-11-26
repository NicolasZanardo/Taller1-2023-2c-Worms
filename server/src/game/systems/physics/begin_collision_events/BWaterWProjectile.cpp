
#include "BWaterWProjectile.h"
#include "../../../model/projectiles/Projectile.h"

void BWaterWProjectile::resolve(Collidable *water_collideable, Collidable *projectile_collideable) {
    auto projec = dynamic_cast<Projectile*>(projectile_collideable);
    if (projec) {
        projec->sink();
    }
}

void BWaterWProjectile::resolve_inverse(Collidable *projectile_collideable, Collidable *water_collideable) {
    resolve(water_collideable, projectile_collideable);
}

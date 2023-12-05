
#include "BWaterWProjectile.h"
#include "Projectile.h"

// TODO Water with project and worm could be the same resolver
void BWaterWProjectile::resolve(Collidable *water_collidable, Collidable *projectile_collidable, b2Contact* contact) {
    auto projec = dynamic_cast<Projectile*>(projectile_collidable);
    if (projec) {
        projec->sink();
    }
}

void BWaterWProjectile::resolve_inverse(Collidable *projectile_collidable, Collidable *water_collidable, b2Contact* contact) {
    resolve(water_collidable, projectile_collidable, contact);
}

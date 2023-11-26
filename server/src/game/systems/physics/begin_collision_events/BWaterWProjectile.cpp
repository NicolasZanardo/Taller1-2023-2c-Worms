
#include "BWaterWProjectile.h"
#include "../../../model/projectiles/Projectile.h"

void BWaterWProjectile::resolve(Collidable *water_collideable, Collidable *projectile_collideable) {
    auto projec = dynamic_cast<Projectile*>(projectile_collideable);
    if (projec) {
        projec->sink();
    }
}

BWaterWProjectile::BWaterWProjectile() {}

void BWaterWProjectile::resolve_inverse(Collidable *water_collideable, Collidable *projectile_collideable) {

}

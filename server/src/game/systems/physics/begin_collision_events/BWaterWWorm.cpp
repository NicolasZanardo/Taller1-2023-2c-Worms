#include "BWaterWWorm.h"
#include "../PhysicsSystem.h"

void BWaterWWorm::resolve(Collidable *water_collidable, Collidable *worm_collidable, b2Manifold* manifold) {
    auto worm = dynamic_cast<Worm*>(worm_collidable);
    if (worm) {
        worm->sink();
    }
}

void BWaterWWorm::resolve_inverse(Collidable *worm_collideable, Collidable *water_collidable, b2Manifold* manifold) {
    resolve(water_collidable, worm_collideable, manifold);
}


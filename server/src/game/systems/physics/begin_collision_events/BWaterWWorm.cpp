#include "BWaterWWorm.h"
#include "../PhysicsSystem.h"

void BWaterWWorm::resolve(Collidable *water_collidable, Collidable *any) {
    auto worm = dynamic_cast<Worm*>(any);
    if (worm) {
        worm->sink();
    }
}

void BWaterWWorm::resolve_inverse(Collidable *water_collideable, Collidable *worm_collideable) {
    resolve(worm_collideable, water_collideable);
}


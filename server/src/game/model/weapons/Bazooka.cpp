#include "Bazooka.h"


Bazooka::Bazooka(int ammo_left, Damage damage) : Weapon(ammo_left, damage) {}


void Bazooka::start_shooting(std::shared_ptr<Worm> shooter) {
    --ammo_left;
    shooter.
}

void Bazooka::end_shooting(std::shared_ptr<Worm> shooter) {
    // TODO()
}
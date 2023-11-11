#include "PhysicsCollisionListener.h"
#include "../game/model/instances/Instance.h"

void PhysicsCollisionListener::BeginContact(b2Contact *contact) {
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    Instance* instanceA = reinterpret_cast<Instance*>(fixtureA->GetUserData().pointer);
    Instance* instanceB = reinterpret_cast<Instance*>(fixtureB->GetUserData().pointer);

    // Collision between worms doesnt trigger anything

    /* TODO Components?
    if (instanceA && instanceB && instanceA->HasComponent<DamageComponent>() && instanceB->HasComponent<HealthComponent>()) {
        DamageComponent& damage = entityA->GetComponent<DamageComponent>();
        HealthComponent& health = entityB->GetComponent<HealthComponent>();
        health.TakeDamage(damage.GetDamage());
    }*/
}

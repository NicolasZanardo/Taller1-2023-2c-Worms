#include "PhysicsCollisionListener.h"
#include "../model/instances/Instance.h"

void PhysicsCollisionListener::BeginContact(b2Contact *contact) {
    /*b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // Assuming that user data for fixtures contains references to the corresponding entities.
    Instance* instance = (Instance*)fixtureA->GetUserData();
    Instance* instanceA = static_cast<Instance*>(fixtureA->GetUserData());
    Instance* instanceB = static_cast<Instance*>(fixtureB->GetUserData());

    // Check if entityA has a DamageComponent and entityB has a HealthComponent.
    if (entityA && entityB && entityA->HasComponent<DamageComponent>() && entityB->HasComponent<HealthComponent>()) {
        DamageComponent& damage = entityA->GetComponent<DamageComponent>();
        HealthComponent& health = entityB->GetComponent<HealthComponent>();
        health.TakeDamage(damage.GetDamage());
    }*/
}

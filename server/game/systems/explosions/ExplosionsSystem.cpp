#include "ExplosionsSystem.h"
#include "OnExplosionWormsQuery.h"


ExplosionsSystem::ExplosionsSystem(
    InstancesManager &instances_manager,
    b2World& world
    ): instances_manager(instances_manager), world(world) {}

void ExplosionsSystem::update(const std::vector<std::shared_ptr<Projectile>> &projectiles)  {
    for (const auto&  projectile: projectiles) {
        auto explosion = projectile->explosion_component();
        if (explosion) {
            auto fragments = projectile->fragments_component();
            if (fragments) {
                for (int i = 0; i < fragments->info()->amount; i++) {
                    instantiate_individual_fragment(i, fragments->info(), explosion);
                }
            }
            OnExplosionWormsQuery::act_on_found(world, std::move(explosion));
            projectile->Destroy();
        }
    }
}

void ExplosionsSystem::instantiate_individual_fragment(
    int actual,
    const std::unique_ptr<FragmentsInfo>& info,
    const std::unique_ptr<CExplosion>& explosion
    ) {
    float fragmentAngle = (2 * b2_pi * actual / info->amount);
    float fragment_speed_magnitude = explosion->max_damage * FRAGMENTS_EXPLOSION_CONSTANT;
    b2Vec2 fragment_speed(
        fragment_speed_magnitude * std::cos(fragmentAngle),
        fragment_speed_magnitude * std::sin(fragmentAngle)
        );

    // Instantiate a fragment projectile with the calculated direction and velocity
    instances_manager.instantiate_fragment_projectile(
        info,
        explosion->x,
        explosion->y,
        fragment_speed
    );
}


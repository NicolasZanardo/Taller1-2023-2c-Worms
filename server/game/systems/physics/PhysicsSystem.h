#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <memory>
#include <unordered_map>
#include "box2d/box2d.h"
#include "GameScenarioData.h"
#include "Worm.h"
#include "constants.h"
#include "PhysicsCollisionListener.h"
#include "Projectile.h"
#include "ScenarioBeams.h"
#include "ScenarioWater.h"
#include "ScenarioBoundaries.h"
#include "WormBody.h"


class PhysicsSystem {
public:
    PhysicsSystem(int rate, b2World& world, const GameScenarioData &map);

    void update();

    std::unique_ptr<WormBody> spawn_worm(
        WormScenarioData wormScenarioData,
        WormCfg &worms_cfg
        );

    std::unique_ptr<ProjectileBody> spawn_projectile(
        const std::unique_ptr<ProjectileInfo> &projectile_info,
        const std::shared_ptr<Projectile> &projectile
    );

    std::unique_ptr<ProjectileBody> spawn_fragment_projectile(
        const std::shared_ptr<Projectile> &projectile,
        const std::unique_ptr<FragmentsInfo>& info,
        float x,
        float y,
        b2Vec2 speed
    );

    // NOT USING 1 as it is the default one
    static const short WORM_CATEGORY_BIT = 2;
    static const short GROUND_CATEGORY_BIT = 4;
    static const short PROJECTILE_CATEGORY_BIT = 8;
    static const short WATER_CATEGORY_BIT = 16;
    static const short BOUNDARY_CATEGORY_BIT = 32;

private:
    const float timeStep;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2World &world;

    ScenarioBeams beams;
    ScenarioWater water;
    ScenarioBoundaries boundaries;
    PhysicsCollisionListener contactListener;

    void populate_beams(const GameScenarioData &map);

    void spawn_beam(BeamScenarioData beam);

    void spawn_water(const GameScenarioData & scenario_data);

    void spawn_boundaries(const GameScenarioData & scenario_data);

    static void set_fixture_filter(b2Fixture* fixture, uint16 categoryBits, uint16 maskBits);

    std::pair<float, float> angle_to_normalized_vector(float angleDegrees);



};

#endif

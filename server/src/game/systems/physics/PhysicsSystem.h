#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <memory>
#include <unordered_map>
#include "box2d/box2d.h"
#include "../../scenario/GameScenarioData.h"
#include "../../model/worm/Worm.h"
#include "../../../../../common_base/constants.h"
#include "PhysicsCollisionListener.h"
#include "../../model/projectiles/Projectile.h"
#include "../../model/collidables/ScenarioBeams.h"
#include "../../model/collidables/ScenarioWater.h"


class PhysicsSystem {
public:
    PhysicsSystem(int rate, float xGravity, float yGravity, const GameScenarioData &map);

    void update(const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms);

    std::unique_ptr<WormBody> spawn_worm(
        WormScenarioData wormScenarioData,
        const std::shared_ptr<Worm> &worm_model
        );

    std::unique_ptr<ProjectileBody> spawn_projectile(
        const std::unique_ptr<ProjectileInfo> &projectile_info,
        const std::shared_ptr<Projectile> &projectile
    );

    // NOT USING 1 as it is the default one
    static const short WORM_CATEGORY_BIT = 2;
    static const short GROUND_CATEGORY_BIT = 4;
    static const short PROJECTILE_CATEGORY_BIT = 8;
    static const short WATER_CATEGORY_BIT = 16;

private:
    const float timeStep;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2World world;

    ScenarioBeams beams; // TODO move to a Map class
    ScenarioWater water; //
    PhysicsCollisionListener contactListener;

    void populate_beams(const GameScenarioData &map);

    void spawn_beam(BeamScenarioData beam);

    void spawn_water(const GameScenarioData & scenario_data);

    std::pair<float, float> angle_to_normalized_vector(float angleDegrees);



};

#endif

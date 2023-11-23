#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <memory>
#include <unordered_map>
#include "box2d/box2d.h"
#include "../../scenario/GameScenarioData.h"
#include "../../model/worm/Worm.h"
#include "../../../../../common_base/constants.h"
#include "PhysicsCollisionListener.h"

class PhysicsSystem {
public:
    PhysicsSystem(int rate, float xGravity, float yGravity, const GameScenarioData &map);

    void update(const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms);

    b2Body *spawn_worm(WormScenarioData wormScenarioData, std::shared_ptr<Worm> wormModel);
    b2Body* spawn_projectile(const std::shared_ptr<ProjectileInfo>& projectile, float shot_angle);

private:
    // Define category bits for fixtures
    const uint16_t WORM_CATEGORY = 0x0001;
    const uint16_t GROUND_CATEGORY = 0x0002;
    const uint16_t PROJECTILE_CATEGORY = 0x0003;

    const float timeStep;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2World world;
    PhysicsCollisionListener contactListener;

    void populate_beams(const GameScenarioData &map);

    void spawn_beam(BeamScenarioData beam);
    std::pair<float, float> angle_to_normalized_vector(float angleDegrees);

};

#endif

#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <box2d/box2d.h>
#include "../../../common_base/Networking/dtos/GameScenarioData.h"
#include "../model/instances/Worm.h"

class PhysicsSystem {
public:
    PhysicsSystem(float xGravity, float yGravity, const GameScenarioData& map);
    void update();
    b2Body* spawn_worm(WormScenarioData wormScenarioData, Worm* wormModel);
private:
    b2World world;
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    void populate_beams(const GameScenarioData& map);
    void spawn_beam(BeamScenarioData beam);

};

#endif

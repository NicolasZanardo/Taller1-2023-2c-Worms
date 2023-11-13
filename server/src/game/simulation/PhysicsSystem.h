#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <unordered_map>
#include "box2d/box2d.h"
#include "../scenario/GameScenarioData.h"
#include "../model/instances/Worm.h"

class PhysicsSystem {
public:
    PhysicsSystem(int rate, float xGravity, float yGravity, const GameScenarioData &map);

    void update(const std::unordered_map<size_t, Worm *> &worms);

    b2Body *spawn_worm(WormScenarioData wormScenarioData, Worm *wormModel);

private:
    const float timeStep;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2World world;

    void populate_beams(const GameScenarioData &map);

    void spawn_beam(BeamScenarioData beam);

};

#endif

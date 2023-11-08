#ifndef SERVER_PHYSICSSYSTEM_H
#define SERVER_PHYSICSSYSTEM_H

#include <box2d/box2d.h>
#include "../model/GameScenario.h"

class PhysicsSystem {
public:
    PhysicsSystem(float xGravity, float yGravity, const GameScenario& map);
    void update();
private:
    b2World world;
    const float timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    void populateWorld(const GameScenario& map);
    void spawnBeam(BeamOnMapDto beam);
    void spawnWorm(WormOnMapDto worm);

};

#endif

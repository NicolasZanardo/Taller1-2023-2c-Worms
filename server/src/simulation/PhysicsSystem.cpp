#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(
        float xGravity,
        float yGravity,
        const GameScenario& map
        ): world(b2Vec2(xGravity, yGravity)) {

}

void PhysicsSystem::update() {
    world.Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsSystem::populateWorld(const GameScenario& scenario) {
    for (auto beam: scenario.beams) {
        spawnBeam(beam);
    }
    for (auto worm: scenario.worms) {
        spawnWorm(worm);
    }
}

void PhysicsSystem::spawnBeam(BeamOnMapDto beam) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(beam.x, beam.y);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    if (beam.type == SHORT) {
        groundBox.SetAsBox(0.80f, 3.0f);
    } else {
        groundBox.SetAsBox(0.80f, 6.0f);
    }

    groundBody->CreateFixture(&groundBox, 0.0f);
}

void PhysicsSystem::spawnWorm(WormOnMapDto worm) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    // bodyDef.fixedRotation = false;
    bodyDef.position.Set(worm.x, worm.y);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(0.5f, 0.5f); // TODO

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;
    // Override the default friction.
    fixtureDef.friction = 0.3f;

    body->CreateFixture(&fixtureDef);
}
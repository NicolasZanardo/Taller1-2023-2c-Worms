#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(
        float xGravity,
        float yGravity,
        const GameScenarioData& scenario
        ): world(b2Vec2(xGravity, yGravity)) {
    populate_beams(scenario);
}

void PhysicsSystem::update() {
    world.Step(timeStep, velocityIterations, positionIterations);
}

b2Body* PhysicsSystem::spawn_worm(WormScenarioData worm, Worm* wormModel) {
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
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&wormModel);;
    body->CreateFixture(&fixtureDef);

    return body;
}

/* PRIVATE */

void PhysicsSystem::populate_beams(const GameScenarioData& scenario) {
    for (auto beam: scenario.beams) {
        spawn_beam(beam);
    }
}

void PhysicsSystem::spawn_beam(BeamScenarioData beam) {
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(beam.x, beam.y);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    if (beam.type == BeamType::SHORT) {
        groundBox.SetAsBox(0.80f, 3.0f);
    } else {
        groundBox.SetAsBox(0.80f, 6.0f);
    }

    groundBody->CreateFixture(&groundBox, 0.0f);
}
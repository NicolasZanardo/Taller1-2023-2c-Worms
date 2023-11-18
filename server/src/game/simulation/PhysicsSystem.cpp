#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(
        int rate,
        float xGravity,
        float yGravity,
        const GameScenarioData& scenario
        ):
        timeStep(1.0f / rate),
        world(b2Vec2(xGravity, yGravity)) {
    populate_beams(scenario);
}

void PhysicsSystem::update(const std::unordered_map<size_t, std::shared_ptr<Worm>>& worms) {
    world.Step(timeStep, velocityIterations, positionIterations);
    for (const auto& [_, worm] : worms) {
        if (worm->movement) {
            worm->movement->on_update_physics();
        }
    }
}

b2Body* PhysicsSystem::spawn_worm(WormScenarioData worm, std::shared_ptr<Worm> wormModel) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(worm.x, worm.y);
    // bodyDef.linearDamping = 0.0f;
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(WORM_SIZE / 2, WORM_SIZE / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    fixtureDef.density = 80.0f;
    //fixtureDef.restitution = 0;
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
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(beam.x, beam.y);
    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    if (beam.type == BeamScenarioData::Type::SHORT) {
        groundBox.SetAsBox(SHORT_BEAM_WIDTH / 2, SHORT_BEAM_HEIGHT / 2);
    } else {
        groundBox.SetAsBox(LARGE_BEAM_WIDTH / 2, LARGE_BEAM_HEIGHT / 2);
    }

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 1000;
    fixtureDef.restitution = 0;

    // Set the friction based on the angle of the ground
    float groundAngle = groundBody->GetAngle();
    float maxWalkableAngle = MAX_BEAM_WALKABLE_ANGLE;

    if (std::abs(groundAngle) <= maxWalkableAngle) {
        fixtureDef.friction = 0.8f;  // Friction for walking
    } else {
        fixtureDef.friction = 0.01f; // Lower friction for sliding
    }

    groundBody->CreateFixture(&fixtureDef);
}
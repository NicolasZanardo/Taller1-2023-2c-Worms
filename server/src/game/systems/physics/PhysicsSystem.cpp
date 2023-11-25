#include "PhysicsSystem.h"
#include <iostream>

const float DEG_TO_RAD = M_PI / 180.0f;

PhysicsSystem::PhysicsSystem(
    int rate,
    float xGravity,
    float yGravity,
    const GameScenarioData &scenario
) :
    timeStep(1.0f / rate),
    world(b2Vec2(xGravity, yGravity)),
    contactListener(world) {
    populate_beams(scenario);
    world.SetContactListener(&contactListener);
}

void PhysicsSystem::update(const std::unordered_map<size_t, std::shared_ptr<Worm>> &worms) {
    world.Step(timeStep, velocityIterations, positionIterations);
}

std::unique_ptr<WormBody> PhysicsSystem::spawn_worm(WormScenarioData worm, std::shared_ptr<Worm> wormModel) {
    // Body def
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(worm.x, worm.y);
    // bodyDef.linearDamping = 0.0f;
    b2Body *body = world.CreateBody(&bodyDef);

    // Shape for hitbox
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = WORM_SIZE / 2;

    // Fixture for hitbox
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    fixtureDef.density = 80.0f;
    fixtureDef.restitution = 0;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(wormModel.get());
    fixtureDef.filter.categoryBits = WORM_CATEGORY;
    fixtureDef.filter.maskBits = GROUND_CATEGORY;
    body->CreateFixture(&fixtureDef);

    // Shape for foot sensor
    b2PolygonShape footSensorBox;
    float sensorHeight = WORM_SIZE / 4;
    footSensorBox.SetAsBox(
        WORM_SIZE / 2,
        sensorHeight,
        b2Vec2(0.0f, -(WORM_SIZE / 2) - (sensorHeight / 2)),
        0
    );

    // Fixture for foot sensor
    b2FixtureDef footSensorFixtureDef;
    footSensorFixtureDef.shape = &footSensorBox;
    footSensorFixtureDef.isSensor = true; // Set as sensor to detect collisions without generating a response
    footSensorFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(wormModel.get()); // same user data
    fixtureDef.filter.categoryBits = WORM_CATEGORY;
    fixtureDef.filter.maskBits = GROUND_CATEGORY | WORM_CATEGORY;
    body->CreateFixture(&footSensorFixtureDef);

    return std::make_unique<WormBody>(world, body);
}

/* PRIVATE */

void PhysicsSystem::populate_beams(const GameScenarioData &scenario) {
    for (auto beam: scenario.beams) {
        spawn_beam(beam);
    }
}

void PhysicsSystem::spawn_beam(BeamScenarioData beam) {
    b2BodyDef groundBodyDef;
    groundBodyDef.type = b2_staticBody;
    groundBodyDef.position.Set(beam.x, beam.y);
    b2Body *groundBody = world.CreateBody(&groundBodyDef);

    float xcenter, ycenter;
    b2PolygonShape groundBox;
    if (beam.type == BeamScenarioData::Type::SHORT) {
        xcenter = SHORT_BEAM_WIDTH / 2;
        ycenter = SHORT_BEAM_HEIGHT / 2;
    } else {
        xcenter = LARGE_BEAM_WIDTH / 2;
        ycenter = LARGE_BEAM_HEIGHT / 2;
    }
    groundBox.SetAsBox(xcenter, ycenter, b2Vec2(xcenter, ycenter), beam.angle * DEG_TO_RAD);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 100;
    fixtureDef.filter.categoryBits = GROUND_CATEGORY;
    // Set the friction based on the angle of the ground
    float groundAngle = groundBody->GetAngle();

    if (std::abs(groundAngle) <= MAX_BEAM_WALKABLE_ANGLE) {
        fixtureDef.friction = 0.8f;  // Friction for walking
    } else {
        fixtureDef.friction = 0.005f; // Lower friction for sliding
    }

    groundBody->CreateFixture(&fixtureDef);
}

std::unique_ptr<ProjectileBody> PhysicsSystem::spawn_projectile(
    const std::unique_ptr<ProjectileInfo> &projectile_info,
    float shot_angle,
    const std::shared_ptr<Projectile> &projectile
) {
    // Body def
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(projectile_info->origin_x, projectile_info->origin_y);
    // bodyDef.linearDamping = 0.0f;
    b2Body *body = world.CreateBody(&bodyDef);

    // Shape for hitbox
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = projectile_info->radius;

    // Fixture for hitbox
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = PROJECTILE_DENSITY;
    fixtureDef.restitution = 0;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(projectile.get());
    fixtureDef.filter.categoryBits = PROJECTILE_CATEGORY;
    fixtureDef.filter.maskBits = GROUND_CATEGORY | WORM_CATEGORY;
    body->CreateFixture(&fixtureDef);

    // Fixture for explosion radius sensor
    b2CircleShape explosionShape;
    explosionShape.m_radius = projectile_info->damage_radius();

    b2FixtureDef explosionSensorDef;
    explosionSensorDef.shape = &explosionShape;
    explosionSensorDef.isSensor = true;
    explosionSensorDef.filter.categoryBits = EXPLOSION_SENSOR_CATEGORY;
    explosionSensorDef.filter.maskBits = WORM_CATEGORY;
    explosionSensorDef.userData.pointer = reinterpret_cast<uintptr_t>(projectile.get());

    // Attach the fixture to the body
    body->CreateFixture(&explosionSensorDef);

    // Apply initial force (adjust values as needed)
    auto aim_vector = angle_to_normalized_vector(shot_angle);
    b2Vec2 initialForce(
        aim_vector.first * projectile_info->power * SHOOT_POTENCY,
        aim_vector.second * projectile_info->power * SHOOT_POTENCY
    );
    body->ApplyLinearImpulse(initialForce, body->GetWorldCenter(), true);

    return std::make_unique<ProjectileBody>(world, body);
}

std::pair<float, float> PhysicsSystem::angle_to_normalized_vector(float angle_degrees) {
    // Convert degrees to radians
    float angle_radians = angle_degrees * M_PI / 180.0f;

    // Calculate the normalized vector components using trigonometry
    float x = std::cos(angle_radians);
    float y = std::sin(angle_radians);

    // Return the result as a pair of floats
    return std::make_pair(x, y);
}

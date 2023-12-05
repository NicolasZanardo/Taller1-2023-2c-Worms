#include "PhysicsSystem.h"
#include "Logger.h"
#include "OnExplosionWormsQuery.h"

const float DEG_TO_RAD = M_PI / 180.0f;

PhysicsSystem::PhysicsSystem(
    int rate,
    b2World &world,
    const GameScenarioData &scenario
) :
    timeStep(1.0f / rate),
    world(world),
    beams(),
    water(),
    boundaries(),
    contactListener() {
    populate_beams(scenario);
    spawn_water(scenario);
    spawn_boundaries(scenario);
    world.SetContactListener(&contactListener);
}

void PhysicsSystem::update() {
    world.Step(timeStep, velocityIterations, positionIterations);
}

std::unique_ptr<WormBody> PhysicsSystem::spawn_worm(
    const std::shared_ptr<Worm> &worm_model,
    WormScenarioData worm,
    WormCfg &worms_cfg
    ) {
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

    fixtureDef.density = worms_cfg.body.density;
    fixtureDef.restitution = worms_cfg.body.restitution;
    fixtureDef.friction = 0.5;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(worm_model.get());
    fixtureDef.filter.categoryBits = WORM_CATEGORY_BIT;
    fixtureDef.filter.maskBits = GROUND_CATEGORY_BIT | PROJECTILE_CATEGORY_BIT | WATER_CATEGORY_BIT | BOUNDARY_CATEGORY_BIT;
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
    footSensorFixtureDef.density = 0;
    footSensorFixtureDef.shape = &footSensorBox;
    footSensorFixtureDef.isSensor = true; // Set as sensor to detect collisions without generating a response
    footSensorFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(worm_model->get_foot_sensor());
    fixtureDef.filter.categoryBits = WORM_CATEGORY_BIT;
    fixtureDef.filter.maskBits = GROUND_CATEGORY_BIT | WATER_CATEGORY_BIT | BOUNDARY_CATEGORY_BIT;
    body->CreateFixture(&footSensorFixtureDef);

    return std::make_unique<WormBody>(world, body, worms_cfg);
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
    if (beam.type == BeamScenarioData::Type::SHORT) {
        xcenter = SHORT_BEAM_WIDTH / 2;
        ycenter = SHORT_BEAM_HEIGHT / 2;
    } else {
        xcenter = LARGE_BEAM_WIDTH / 2;
        ycenter = LARGE_BEAM_HEIGHT / 2;
    }

    b2PolygonShape groundBox;
    groundBox.SetAsBox(xcenter, ycenter, b2Vec2(0, 0), beam.angle * DEG_TO_RAD);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundBox;
    fixtureDef.density = 100;
    fixtureDef.filter.categoryBits = GROUND_CATEGORY_BIT;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(&beams);
    // Set the friction based on the angle of the ground
    float groundAngle = groundBody->GetAngle();

    if (std::abs(groundAngle) <= MAX_BEAM_WALKABLE_ANGLE) {
        fixtureDef.friction = 1;  // Friction for walking granades sliding
    } else {
        fixtureDef.friction = 0.005f; // Lower friction for sliding
    }

    groundBody->CreateFixture(&fixtureDef);
}

std::unique_ptr<ProjectileBody> PhysicsSystem::spawn_projectile(
    const std::unique_ptr<ProjectileInfo> &projectile_info,
    const std::shared_ptr<Projectile> &projectile
) {
    // Body def
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;

    std::unique_ptr<RotationStrategy> rotation_strategy = nullptr;
    switch(projectile_info->rotation_type) {
        case RotationType::NONE:
            bodyDef.fixedRotation = true;
            break;
        case RotationType::VELOCITY_ALIGNED:
            rotation_strategy = std::make_unique<VelocityAlignedRotation>();
            break;
        case RotationType::INITIAL_ANGULAR_VELOCITY:
            bodyDef.angularVelocity = -5 * projectile_info->facing_sign; // TODO Check sign
            break;
    }

    auto aim_vector = angle_to_normalized_vector(projectile_info->shot_angle);
    bool is_facing_right = true;
    if (projectile_info->facing_sign == -1) {
        is_facing_right = false;
        aim_vector.first *= -1.0f;  // Reverse the x-component for left-facing shot
    }

    b2Vec2 initial_force(
        aim_vector.first * projectile_info->power,
        aim_vector.second * projectile_info->power
    );

    b2Vec2 offset_from_worm(aim_vector.first * SHOT_OFFSET_FROM_WORM, aim_vector.second * SHOT_OFFSET_FROM_WORM);
    bodyDef.position.Set(projectile_info->origin_x + offset_from_worm.x,
                         projectile_info->origin_y + offset_from_worm.y);

    b2Body *body = world.CreateBody(&bodyDef);

    // Shape for hitbox
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = PROJECTILE_RADIUS; // todo cfg

    // b2PolygonShape dynamicCircle;
    // dynamicCircle.SetAsBox(PROJECTILE_RADIUS, PROJECTILE_RADIUS * 2, b2Vec2(0, 0), 0);

    // Fixture for hitbox
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = PROJECTILE_DENSITY;
    fixtureDef.friction = 1;
    fixtureDef.restitution = 0;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(projectile.get());
    fixtureDef.filter.categoryBits = PROJECTILE_CATEGORY_BIT;
    fixtureDef.filter.maskBits = GROUND_CATEGORY_BIT | WORM_CATEGORY_BIT | WATER_CATEGORY_BIT | BOUNDARY_CATEGORY_BIT;
    body->CreateFixture(&fixtureDef);

    body->ApplyLinearImpulse(initial_force, body->GetWorldCenter(), true);
    body->SetAngularDamping(0.1f);
    return std::make_unique<ProjectileBody>(world, body, is_facing_right, std::move(rotation_strategy));
}

std::pair<float, float> PhysicsSystem::angle_to_normalized_vector(float angle_degrees) {
    // Convert degrees to radians
    float angle_radians = angle_degrees * DEG_TO_RAD;

    float x = std::cos(angle_radians);
    float y = std::sin(angle_radians);
    return std::make_pair(std::abs(x), y);
}

void PhysicsSystem::spawn_water(const GameScenarioData &scenario_data) {
    b2BodyDef water_body_def;
    water_body_def.type = b2_staticBody;
    water_body_def.position.Set(
        scenario_data.room_width / 2,
        scenario_data.water_height_level - (WATER_HEIGHT / 2)
    );
    b2Body *water_body = world.CreateBody(&water_body_def);


    b2PolygonShape water_box;
    water_box.SetAsBox((scenario_data.room_width + 10) / 2, WATER_HEIGHT / 2);

    b2FixtureDef fixture_def;
    fixture_def.shape = &water_box;
    fixture_def.filter.categoryBits = WATER_CATEGORY_BIT;
    fixture_def.filter.maskBits = WORM_CATEGORY_BIT | PROJECTILE_CATEGORY_BIT;
    fixture_def.userData.pointer = reinterpret_cast<uintptr_t>(&water);
    fixture_def.isSensor = true;
    water_body->CreateFixture(&fixture_def);
}

std::unique_ptr<ProjectileBody>
PhysicsSystem::spawn_fragment_projectile(
    const std::shared_ptr<Projectile> &projectile,
    const std::unique_ptr<FragmentsInfo> &info,
    float x,
    float y,
    b2Vec2 speed
) {

    // Body def
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    // Logger::log_position("A projectile spawned", projectile_info->origin_x + offset_from_worm.x,projectile_info->origin_y + offset_from_worm.y);
    bodyDef.position.Set(x, y);
    // bodyDef.linearDamping = 0.0f;
    b2Body *body = world.CreateBody(&bodyDef);

    std::unique_ptr<RotationStrategy> rotation_strategy = nullptr;

    // Shape for hitbox
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = PROJECTILE_RADIUS;

    // Fixture for hitbox
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;
    fixtureDef.density = PROJECTILE_DENSITY;
    fixtureDef.restitution = 0;
    fixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(projectile.get());
    fixtureDef.filter.categoryBits = PROJECTILE_CATEGORY_BIT;
    fixtureDef.filter.maskBits = GROUND_CATEGORY_BIT | WORM_CATEGORY_BIT | WATER_CATEGORY_BIT | BOUNDARY_CATEGORY_BIT;
    body->CreateFixture(&fixtureDef);
    body->ApplyLinearImpulse(speed, body->GetWorldCenter(), true);
    bool is_facing_right = true;
    if (speed.x < 0) {
        is_facing_right = false;
    }
    return std::make_unique<ProjectileBody>(world, body, is_facing_right, nullptr);
}

void PhysicsSystem::spawn_boundaries(const GameScenarioData &scenario_data) {

    b2EdgeShape top_edge, bottom_edge, left_edge, right_edge;
    b2BodyDef boundaryBodyDef;

    // Top boundary
    top_edge.SetTwoSided(b2Vec2(0, scenario_data.room_height), b2Vec2(scenario_data.room_width, scenario_data.room_height));
    boundaryBodyDef.type = b2_staticBody;
    b2Body* top_body = world.CreateBody(&boundaryBodyDef);
    b2Fixture* top_fixture = top_body->CreateFixture(&top_edge, 0.0f);
    top_fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(&boundaries);

    // Bottom boundary
    bottom_edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(scenario_data.room_width, 0));
    b2Body* bottom_body = world.CreateBody(&boundaryBodyDef);
    b2Fixture* bottom_fixture = bottom_body->CreateFixture(&bottom_edge, 0.0f);
    bottom_fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(&boundaries);

    // Left boundary
    left_edge.SetTwoSided(b2Vec2(0, 0), b2Vec2(0, scenario_data.room_height));
    b2Body* left_body = world.CreateBody(&boundaryBodyDef);
    b2Fixture* left_fixture = left_body->CreateFixture(&left_edge, 0.0f);
    left_fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(&boundaries);

    // Right boundary
    right_edge.SetTwoSided(b2Vec2(scenario_data.room_width, 0), b2Vec2(scenario_data.room_width, scenario_data.room_height));
    b2Body* right_body = world.CreateBody(&boundaryBodyDef);
    b2Fixture* right_fixture = right_body->CreateFixture(&right_edge, 0.0f);
    right_fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(&boundaries);

    set_fixture_filter(top_fixture, BOUNDARY_CATEGORY_BIT, PROJECTILE_CATEGORY_BIT | WORM_CATEGORY_BIT);
    set_fixture_filter(bottom_fixture, BOUNDARY_CATEGORY_BIT, PROJECTILE_CATEGORY_BIT | WORM_CATEGORY_BIT);
    set_fixture_filter(left_fixture, BOUNDARY_CATEGORY_BIT, PROJECTILE_CATEGORY_BIT | WORM_CATEGORY_BIT);
    set_fixture_filter(right_fixture, BOUNDARY_CATEGORY_BIT, PROJECTILE_CATEGORY_BIT | WORM_CATEGORY_BIT);
}

void PhysicsSystem::set_fixture_filter(b2Fixture* fixture, uint16 categoryBits, uint16 maskBits) {
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = categoryBits;
    filter.maskBits = maskBits;
    fixture->SetFilterData(filter);
}

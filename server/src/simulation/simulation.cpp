#include "simulation.h"
#include <unistd.h>
#include <box2d/box2d.h>
#include <iomanip>
#include <iostream>
using namespace std;

void display(b2Body* bodyA, const char* name) {
	cout << name << " >> X:"<< bodyA->GetPosition().x << " Y:" << bodyA->GetPosition().y << " Angle:"<< bodyA->GetAngle()*360/(2*M_PI) <<"\n";
}


void Simulation::begin() {
    cout << "    Begin simulation. \n\n\n\n";
	cout << fixed << setprecision(2);
	
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = false;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	bodyDef.position.Set(-1.1f, 2.0f);
	b2Body* body2 = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);
	body2->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float timeStep = 1.0f / 10.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	// This is our little game loop.
	for (int32 i = 0; i < 25; ++i)
	{
		if (i == 20) {
			b2Vec2 jump(1.0f, -3.0f);
			body->SetAwake(true);
			body2->SetAwake(true);
			body2->SetLinearVelocity(jump);
		}

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);
		
		cout << "\033[4A";
		cout << "------------ENTITIES-ON-STEP-"<< i <<"----------------\n";
		display(body, "Body 1");
		display(body2, "Body 2");
		cout << "----------------------------------------------\n";
		sleep(1);
	}
}

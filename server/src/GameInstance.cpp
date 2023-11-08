#include "GameInstance.h"

GameInstance::GameInstance(const GameScenario& scenario) : clientWormsMap(),
                                               gameQueue(50),
                                               physicsSystem(0.0f, -10.0f, scenario) {}

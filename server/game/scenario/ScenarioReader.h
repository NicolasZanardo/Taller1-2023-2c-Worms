#ifndef SERVER_SCENARIOREADER_H
#define SERVER_SCENARIOREADER_H

#include <string>
#include "GameScenarioData.h"
#include "HardcodedScenarioData.h"

class ScenarioReader {
public:
    GameScenarioData readScenario(std::string filePath);
};

#endif

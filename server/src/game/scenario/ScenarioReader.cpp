#include "ScenarioReader.h"

GameScenarioData ScenarioReader::readScenario(std::string filePath) {
    return HardcodedScenarioData::get();
}
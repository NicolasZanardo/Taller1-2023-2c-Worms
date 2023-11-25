#include "Logger.h"
#include <iostream>

void Logger::log_position(const std::string& log, float x, float y) {
    std::cout << log << " on x: " << x << " y: " << y << std::endl;
}

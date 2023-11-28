#ifndef TP_WORMS_LOGGER_H
#define TP_WORMS_LOGGER_H

#include <string>
#include "../../../../common_base/Game/WeaponTypeDto.h"

class Logger {
public:
    static void log_position(const std::string& log, float x, float y);
    static void log_weapon(const std::string &log, WeaponTypeDto weapon);

    Logger() = delete;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&& other) = delete;
    Logger& operator=(Logger&& other) = delete;
};


#endif

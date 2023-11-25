#ifndef TP_WORMS_LOGGER_H
#define TP_WORMS_LOGGER_H

#include <string>

class Logger {
public:
    static void log_position(const std::string& log, float x, float y);
};


#endif

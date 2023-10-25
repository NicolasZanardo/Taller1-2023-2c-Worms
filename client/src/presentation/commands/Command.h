#ifndef COMMAND_H
#define COMMAND_H

#include "../../model/Worm.h"

class Command {
public:
    Command() {}
    virtual ~Command() {}
    virtual void execute(Worm& worm) = 0;
};

#endif

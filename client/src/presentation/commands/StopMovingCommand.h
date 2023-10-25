#ifndef STOPMOVINGCOMMAND_H
#define STOPMOVINGCOMMAND_H

#include "Command.h"

class StopMovingCommand : public Command
{
public:
    StopMovingCommand();
    void execute(Worm& worm);
};

#endif

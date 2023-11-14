#ifndef JUMP_H
#define JUMP_H

#include "Command.h"

class JumpCommand : public Command {
public:
    JumpCommand();
    void execute(Worm& worm);
};

#endif

#ifndef MOVERIGHT_H
#define MOVERIGHT_H

#include "Command.h"

enum class MovingDirection {
    RIGHT, LEFT
};

class MoveCommand : public Command
{
public:
    MoveCommand(MovingDirection dir);
    void execute(Worm& worm);

private:
    MovingDirection movingDirection;
};


#endif

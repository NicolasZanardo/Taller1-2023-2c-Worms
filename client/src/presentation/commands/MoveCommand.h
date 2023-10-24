#ifndef MOVERIGHT_H
#define MOVERIGHT_H

class MoveRight : public Command
{
public:
    virtual void execute() { move(); }
};


#endif

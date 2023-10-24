#ifndef WORMS_JUMP_H
#define WORMS_JUMP_H

class Jump : public Command
{
public:
    virtual void execute() { jump(); }
};

#endif //WORMS_JUMP_H

#include "StopMovingCommand.h"

StopMovingCommand::StopMovingCommand(): Command() {}
void StopMovingCommand::execute(Worm& worm) {
    worm.stopMoving();
}
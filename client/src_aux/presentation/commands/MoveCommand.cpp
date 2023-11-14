#include "MoveCommand.h"

MoveCommand::MoveCommand(MovingDirection dir): Command(), movingDirection(dir) {}

void MoveCommand::execute(Worm& worm) {
    if (movingDirection == MovingDirection::RIGHT) {
        worm.moveRight();
    } else {
        worm.moveLeft();
    }
}
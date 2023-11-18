#include "Worm.h"
#include <iostream>

Worm::Worm(size_t id) :
        Instance(id),
        movement(nullptr) {}

WormDto Worm::toWormDto(size_t clientId) {
    return WormDto(
            clientId,
            id,
            movement->x(),
            movement->y(),
            health,
            movement->state_to_dto()
    );
}

// Movement
void Worm::startMovingRight() {
    movement->start_moving_right();
}

void Worm::startMovingLeft() {
    movement->start_moving_left();
}

void Worm::stopMoving() {
    movement->stop_moving();
}

void Worm::jumpForward() {
    movement->jump_forward();
}

void Worm::jumpBackwards() {
    movement->jump_backwards();
}


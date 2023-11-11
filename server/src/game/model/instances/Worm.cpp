#include "Worm.h"

Worm::Worm(size_t id): Instance(id) {}

WormDto Worm::toWormDto(int clientId) {
    b2Vec2 position = body->GetPosition();
    return WormDto(
            clientId,
            id,
            position.x,
            position.y,
            health,
            WormDto::State::idle// Todo Hardcoded Server states do not necessarily map 1 to 1 to the dto states needed by client
            );
}

#include "GameWorldEvent.h"

GameWorldEvent::GameWorldEvent(
    size_t id,
    GameWorldEventType type,
    float x,
    float y
) : Instance(id), type(type), x(x), y(y) {}

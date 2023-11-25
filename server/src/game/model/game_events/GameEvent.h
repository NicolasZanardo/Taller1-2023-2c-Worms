#ifndef TP_WORMS_GAMEEVENT_H
#define TP_WORMS_GAMEEVENT_H

#include "../core/Instance.h"
#include "../../../../../common_base/Game/GameEventType.h"

class GameEvent: public Instance {

    GameEventType type;
    float x;
    float y;
public:
    GameEvent(size_t id, GameEventType type, float x, float y);
};


#endif //TP_WORMS_GAMEEVENT_H

#ifndef TP_WORMS_GAMEWORLDEVENT_H
#define TP_WORMS_GAMEWORLDEVENT_H

#include "../core/Instance.h"
#include "../../../../../common_base/Game/GameWorldEventType.h"

class GameWorldEvent: public Instance {


    GameWorldEventType type;
    int associated_entity_id;
    float x;
    float y;
public:
    GameWorldEvent(size_t id, GameWorldEventType type, float x, float y);
};


#endif //TP_WORMS_GAMEWORLDEVENT_H

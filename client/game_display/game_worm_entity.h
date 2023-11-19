#ifndef _CLIENT_GAME_WORM_ENTITY_H_
#define _CLIENT_GAME_WORM_ENTITY_H_

#include "ui_utils.h"
#include "networking.h"
#include "game_display.h"
#include "game_displayable.h"

class WormEntity {
    WormDto attributes; 
    std::unordered_map<MovementStateDto, Displayable*> animations;
    Displayable* active_animation;
    
    public:
    WormEntity(GameDisplay& display, WormDto& values);
    void update(WormDto& new_values);
};
#endif

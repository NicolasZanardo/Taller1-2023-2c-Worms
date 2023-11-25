#ifndef _CLIENT_GAME_WORM_ENTITY_H_
#define _CLIENT_GAME_WORM_ENTITY_H_

#include "ui_utils.h"
#include "networking.h"
#include "game_display.h"
#include "game_displayable.h"
#include "game_camera.h"
#include "worm_anim_key.h"

class WormEntity : public CameraTarget{
    WormDto attributes; 
    std::unordered_map<WormAnimKey, GameSprite*> animations;
    GameSprite* active_animation;
    bool is_active;
    
    public:
    WormEntity(GameDisplay& display, WormDto& values);
    void update(WormDto& new_values);
    void destroy();

    float get_x() override;
    float get_y() override;
};
#endif

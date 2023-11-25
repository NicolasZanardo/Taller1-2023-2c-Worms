#ifndef _CLIENT_GAME_WORM_ENTITY_H_
#define _CLIENT_GAME_WORM_ENTITY_H_

#include "ui_utils.h"
#include "networking.h"
#include "game_display.h"
#include "game_displayable.h"
#include "game_camera.h"
#include "worm_anim_key.h"
#include "game_sprite.h"
#include "game_text_display.h"
#include "game_worm_animation_set.h"

class WormEntity : public CameraTarget{
    WormDto attributes; 
    WormAnimationSet* sprite;
    bool is_active;
    GameTextDisplay* name;
    
    public:
    WormEntity(GameDisplay& display, WormDto& values);
    void update(WormDto& new_values);

    float get_x() override;
    float get_y() override;
};
#endif
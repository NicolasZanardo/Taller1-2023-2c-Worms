#ifndef CLIENT_ONE_WORM_TO_RULE_THEM_ALL_H_
#define CLIENT_ONE_WORM_TO_RULE_THEM_ALL_H_

#include <iostream>
#include "../game_ui/animation.h"
#include "../game_ui/sprites_manager.h"

struct TheWorm {
    int client_id;
    int entity_id;
    float x;
    float y;
    Animation animation;

    TheWorm(int client_id, int entity_id, float x, float y, SpritesManager& mngr) : 
        client_id(client_id),
        entity_id(entity_id),
        x(x), y(y),
        animation(mngr,"wwalk", FrameSelectorMode::BOUNCE, 12, true)
        {
            
        }

    void update (float x, float y) {
        this->x = x;
        this->y = y;
    }

    void render() {
        animation.render(SDL2pp::Rect(x, y, 50, 50), true);
    }
};
#endif

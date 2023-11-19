#ifndef _CLIENT_GAME_SPRITE_H_
#define _CLIENT_GAME_SPRITE_H_

#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "game_displayable.h"
#include "game_sprite_info.h"

class GameSprite : public Displayable {
    GameSpriteInfo& info;
    SDL2pp::Rect transform;
    float angle;
    bool is_active;
    SDL_RendererFlip flip;
    
    float anim_speed;
    float anim_progress;

    public:
    ~GameSprite() override;
    explicit GameSprite(GameSpriteInfo& info);

    void flip_horizontaly();
    void set_angle(float angle);
    void set_size(float width, float heigth);

    void hidden(bool is_hidden) override;
    void set_pos(float x, float y) override;
    void image_flipped(bool image_is_flipped) override;
    void render(SDL2pp::Renderer& renderer, float delta_time) override;
};

#endif
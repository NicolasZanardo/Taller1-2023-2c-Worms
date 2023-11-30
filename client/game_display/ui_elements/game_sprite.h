#ifndef _CLIENT_GAME_SPRITE_H_
#define _CLIENT_GAME_SPRITE_H_

#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "game_camera.h"
#include "game_displayable.h"
#include "game_sprite_info.h"

class GameSprite : public Displayable {
    GameSpriteInfo& info;
    float x,y,w,h;
    SDL2pp::Rect transform;
    SDL2pp::Point offset;
    float angle, angle_min, angle_max;
    bool is_active;
    SDL_RendererFlip flip;
    
    float anim_speed;
    float anim_progress;
    GameCamera* cam;

    public:
    ~GameSprite() override;
    explicit GameSprite(GameSpriteInfo& info, float width, float height, float angle);
    explicit GameSprite(GameCamera& cam, GameSpriteInfo& info, float width, float height, float angle);

    void set_size(float width, float heigth);

    void set_angle(float angle);
    void set_angle_range(float angle_min, float angle_max);

    void hidden(bool is_hidden);
    void set_pos(float x, float y);
    void image_flipped(bool image_is_flipped);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;

    void update_animation(float delta_time);
    friend class WormAnimationSet;
};

#endif
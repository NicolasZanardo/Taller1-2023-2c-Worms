#include "game_sprite.h"
#include <iostream>

GameSprite::~GameSprite() { }
GameSprite::GameSprite(GameCamera& cam, GameSpriteInfo& info) :
    cam(cam),
    info(info),
    x(0),y(0),w(0),h(0),
    transform(0,0,0,0),
    angle(0.0f),
    is_active(true),
    flip(SDL_FLIP_NONE),
    anim_speed(0.000001f),
    anim_progress(0)
    { }

void GameSprite::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameSprite::set_size(float width, float heigth) {
    this->w = width;
    this->h = heigth;
}

void GameSprite::set_angle(float angle) {
    this->angle = angle;
}

void GameSprite::image_flipped(bool image_is_flipped) {
    flip = image_is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void GameSprite::hidden(bool is_hidden) {
    is_active = !is_hidden;
}

void GameSprite::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (!is_active) return;
    
    cam.body_to_transform(x,y,w,h,transform);
    SDL2pp::Point center(
        (transform.GetW()) / 2,
        (transform.GetH()) / 2
    );

    if (info.frame_count <= 0) {
        renderer.Copy(info.texture,SDL2pp::NullOpt,transform,-angle,center,flip);
        return;
    }


    anim_progress += delta_time * anim_speed * info.frame_speed;
    while (anim_progress > info.frame_count) {
        anim_progress -= info.frame_count;
    }

    renderer.Copy(info.texture, info.image_frame(anim_progress), transform, -angle, SDL2pp::NullOpt, flip);
}

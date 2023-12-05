#include "game_sprite.h"
#include "sprite_animation.h"
#include <iostream>
#include <math.h>

inline float normalize_angle(float angle, float min, float max) {
    angle = 360.0f * (float)(angle < 0) + std::fmod(angle,360);
    
    angle += (float)((min > max)*(angle < min))*360.0f;
    max += (float)(min > max)*360.0f;

    angle += (float)(angle < min)*(min-angle) + (float)(angle > max)*(max-angle);
    return angle - (float)(angle > 360) * 360.0f;
}

GameSprite::~GameSprite() {
    delete(animation);
}

GameSprite::GameSprite(GameCamera& cam, GameSpriteInfo& info, float width, float height, float angle) :
    GameSprite(info, width, height, angle) { this->cam = &cam; }

GameSprite::GameSprite(GameSpriteInfo& info, float width, float height, float angle) :
    info(info),
    x(0),y(0),w(width),h(height),
    transform(0,0,0,0),
    offset(width/2, height/2),
    angle(angle), angle_min(0), angle_max(360),
    is_active(true),
    flip(SDL_FLIP_NONE),
    cam(nullptr),
    animation(info.new_animation())
    {}

void GameSprite::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameSprite::set_size(float width, float heigth) {
    this->w = width;
    this->h = heigth;
}

void GameSprite::set_angle(float angle) {
    this->angle = normalize_angle(angle, angle_min, angle_max);
}

void GameSprite::set_angle_range(float angle_min, float angle_max) {
    this->angle_min = normalize_angle(angle_min, 0.0f, 360.0f);
    this->angle_max = normalize_angle(angle_max, 0.0f, 360.0f);
    this->angle = normalize_angle(this->angle, this->angle_min, this->angle_max);
}

void GameSprite::image_flipped(bool image_is_flipped) {
    flip = image_is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
}

void GameSprite::hidden(bool is_hidden) {
    is_active = !is_hidden;
}

void GameSprite::render(SDL2pp::Renderer& renderer, float delta_time) {
    if (!is_active) return;

    if (cam != nullptr) {
        cam->body_to_transform(x,y,w,h,transform);
        offset.SetX(cam->transform_w(w)/2);
        offset.SetY(cam->transform_h(h)/2);
    } else {
        transform.SetX(x);
        transform.SetY(y);
        transform.SetW(w);
        transform.SetH(h);
        offset.SetX(w/2);
        offset.SetY(h/2);
    }

    if (info.frame_count <= 0) {
        renderer.Copy(info.texture,SDL2pp::NullOpt,transform,normalize_angle(-angle, angle_min, angle_max),offset,flip);
    } else if (info.animation == BY_ANGLE) {
        renderer.Copy(info.texture, animation->update(angle), transform, 0.0, offset, flip);
    } else {
        renderer.Copy(info.texture, animation->update(delta_time), transform, normalize_angle(-angle, angle_min, angle_max), offset, flip);
    }
}

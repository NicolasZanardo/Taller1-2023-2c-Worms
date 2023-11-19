#include "game_sprite.h"

GameSprite::~GameSprite() { }
GameSprite::GameSprite(GameSpriteInfo& info) :
    info(info),
    transform(0,0,0,0),
    angle(0.0f),
    is_active(true),
    flip(SDL_FLIP_NONE),
    anim_speed(0.000001f),
    anim_progress(0)
    { }

void GameSprite::set_pos(float x, float y) {
    transform.SetX(x);
    transform.SetY(y);
}

void GameSprite::set_size(float width, float heigth) {
    transform.SetW(width);
    transform.SetH(heigth);
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

    if (info.frame_count <= 0) {
        renderer.Copy(info.texture,SDL2pp::NullOpt,transform,angle,SDL2pp::NullOpt,flip);
        return;
    }

    anim_progress += delta_time * anim_speed * info.frame_speed;
    while (anim_progress > info.frame_count) {
        anim_progress -= info.frame_count;
    }
    renderer.Copy(info.texture,info.image_frame(anim_progress),transform,angle,SDL2pp::NullOpt,flip);
}

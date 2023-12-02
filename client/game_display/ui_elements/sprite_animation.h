#ifndef _CLIENT_SPRITE_ANIMATION_H_
#define _CLIENT_SPRITE_ANIMATION_H_

#include <math.h>
#include <SDL2pp/SDL2pp.hh>
#include "game_sprite_info.h"

struct SpriteAnimation {
    float speed;
    float progress;
    float framecount;
    GameSpriteInfo& info;
    virtual SDL2pp::Rect update(float deltatime) = 0;
    virtual void restart() {
        progress = 0;
    }
    
    virtual ~SpriteAnimation() {}
    SpriteAnimation(GameSpriteInfo& info) :
        speed(info.frame_speed * 0.000001f), progress(0),
        framecount(info.frame_count), info(info) { }
};

struct NoAnimation : public SpriteAnimation {
    NoAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

    SDL2pp::Rect update(float deltatime) override {
        return info.image_frame(0);
    }
};

struct LoopingAnimation : public SpriteAnimation {
    LoopingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

    void restart() override {
        progress = 0;
        speed = abs(speed);
    }

    SDL2pp::Rect update(float deltatime) override {
        progress += speed * deltatime;
        while (progress >= info.frame_count) {
            progress -= info.frame_count;
        }

        return info.image_frame(progress);
    }
};

struct ReversingAnimation : public SpriteAnimation {
    ReversingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

    SDL2pp::Rect update(float deltatime) override {
        progress += speed * deltatime;
        while (progress >= framecount || progress < 0) {
            float asc = progress > framecount;
            progress = (2*framecount - progress)*asc - progress*(1.0f-asc);
            speed = -speed;

            float stuck = progress == framecount || progress == 0;
            progress += stuck * deltatime * speed / 4.0f;
        }

        return info.image_frame(progress);
    }
};

struct RotationAnimation : public SpriteAnimation {
    float angle_ini;
    float angle_span;

    ~RotationAnimation() override {}
    RotationAnimation(GameSpriteInfo& info, float angle_ini, float angle_span) :
    SpriteAnimation(info),
    angle_ini(angle_ini),
    angle_span(angle_span)
    { }

    SDL2pp::Rect update(float angle) override {
        progress = (framecount+1.0f) * (angle - angle_ini) / (angle_span);

        if (progress >= framecount-1)
            progress = framecount-1;

        return info.image_frame(progress);
    }
};

struct FreezingAnimation : public SpriteAnimation {
    FreezingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

    SDL2pp::Rect update(float deltatime) override {
        progress += speed * deltatime;
        if (progress >= info.frame_count) {
            progress = info.frame_count-1;
        }
        if (progress < 0) {
            progress = 0;
        }

        return info.image_frame(progress);
    }
};

#include "game_display.h"
struct VFXAnimation : public SpriteAnimation {
    GameDisplay* holder;
    Displayable* image;

    VFXAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info), holder(nullptr), 
    image(nullptr) { }

    void setup(GameDisplay& display, Displayable& sprite) {
        image = &sprite;
        holder = &display;
    }

    SDL2pp::Rect update(float deltatime) override {
        progress += speed * deltatime;
        if (progress >= info.frame_count || progress < 0) {
            holder->remove(image);
            return SDL2pp::Rect(0,0,0,0);
        }

        return info.image_frame(progress);
    }
};
#endif
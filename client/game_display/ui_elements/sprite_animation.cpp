#include "sprite_animation.h"
#include "game_display.h"
#include "game_displayable.h"
#include <math.h>


SpriteAnimation::~SpriteAnimation() {}
void SpriteAnimation::restart() {
    progress = 0;
}
SpriteAnimation::SpriteAnimation(GameSpriteInfo& info) :
        speed(info.frame_speed * 0.000001f), progress(0),
        framecount(info.frame_count), info(info) { }





NoAnimation::~NoAnimation() {}
NoAnimation::NoAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

SDL2pp::Rect NoAnimation::update(float deltatime) {
    return info.image_frame(0);
}




LoopingAnimation::~LoopingAnimation() {}
LoopingAnimation::LoopingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

void LoopingAnimation::restart() {
    progress = 0;
    speed = abs(speed);
}

SDL2pp::Rect LoopingAnimation::update(float deltatime) {
    progress += speed * deltatime;
    while (progress >= info.frame_count) {
        progress -= info.frame_count;
    }

    return info.image_frame(progress);
}






ReversingAnimation::~ReversingAnimation() {}
ReversingAnimation::ReversingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

SDL2pp::Rect ReversingAnimation::update(float deltatime) {
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





RotationAnimation::~RotationAnimation() {}
RotationAnimation::RotationAnimation(GameSpriteInfo& info, float angle_ini, float angle_span) :
    SpriteAnimation(info),
    angle_ini(angle_ini),
    angle_span(angle_span)
    { }

SDL2pp::Rect RotationAnimation::update(float angle) {
    progress = (framecount+1.0f) * (angle - angle_ini) / (angle_span);

    if (progress >= framecount-1)
        progress = framecount-1;

    return info.image_frame(progress);
}




FreezingAnimation::~FreezingAnimation() {}
FreezingAnimation::FreezingAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info) { }

SDL2pp::Rect FreezingAnimation::update(float deltatime) {
    progress += speed * deltatime;
    if (progress >= info.frame_count) {
        progress = info.frame_count-1;
    }
    if (progress < 0) {
        progress = 0;
    }

    return info.image_frame(progress);
}





VFXAnimation::~VFXAnimation() {}
VFXAnimation::VFXAnimation(GameSpriteInfo& info) :
    SpriteAnimation(info), holder(nullptr), 
    image(nullptr) { }

void VFXAnimation::setup(GameDisplay& display, Displayable& sprite) {
    image = &sprite;
    holder = &display;
}

SDL2pp::Rect VFXAnimation::update(float deltatime) {
    progress += speed * deltatime;
    if (progress >= info.frame_count || progress < 0) {
        holder->remove(image);
        return SDL2pp::Rect(0,0,0,0);
    }

    return info.image_frame(progress);
}
#ifndef _CLIENT_SPRITE_ANIMATION_H_
#define _CLIENT_SPRITE_ANIMATION_H_

#include <SDL2pp/SDL2pp.hh>
#include "game_sprite_info.h"

struct SpriteAnimation {
    float speed;
    float progress;
    float framecount;
    GameSpriteInfo& info;
    
    virtual ~SpriteAnimation();
    SpriteAnimation(GameSpriteInfo& info);
    virtual SDL2pp::Rect update(float deltatime) = 0;
    virtual void restart();
};

struct NoAnimation : public SpriteAnimation {
    NoAnimation(GameSpriteInfo& info);
    ~NoAnimation() override;
    SDL2pp::Rect update(float deltatime) override;
};

struct LoopingAnimation : public SpriteAnimation {
    ~LoopingAnimation() override;
    LoopingAnimation(GameSpriteInfo& info);
    SDL2pp::Rect update(float deltatime) override;
    void restart() override;
};

struct ReversingAnimation : public SpriteAnimation {
    ~ReversingAnimation() override;
    ReversingAnimation(GameSpriteInfo& info);
    SDL2pp::Rect update(float deltatime) override;
};

struct RotationAnimation : public SpriteAnimation {
    float angle_ini;
    float angle_span;
    ~RotationAnimation() override;
    RotationAnimation(GameSpriteInfo& info, float angle_ini, float angle_span);
    SDL2pp::Rect update(float angle) override;
};

struct FreezingAnimation : public SpriteAnimation {
    ~FreezingAnimation() override;
    FreezingAnimation(GameSpriteInfo& info);
    SDL2pp::Rect update(float deltatime) override;
};

class GameDisplay;
class Displayable;
struct VFXAnimation : public SpriteAnimation {
    GameDisplay* holder;
    Displayable* image;

    ~VFXAnimation() override;
    VFXAnimation(GameSpriteInfo& info);
    void setup(GameDisplay& display, Displayable& sprite);
    SDL2pp::Rect update(float deltatime) override;
};
#endif
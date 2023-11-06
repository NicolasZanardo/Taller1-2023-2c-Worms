/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

#include "./frame_selector.h"
#include "./sprite.h"

#define FRAME_RATE 1000000.0f/25.0f

class Animation {
public:
    Animation() = delete;
    explicit Animation(Sprite& sprite, bool img_looking_left);
    ~Animation() = default;

    void update(float dt);
    void render(const SDL2pp::Rect dest, bool facing_right);

private:
    bool img_looking_left;  // Sprite image orientarion.
    float elapsed;  // Time elapsed since last update.
    FrameSelector frame_selector;
    Sprite* sprite;
};

#endif  //__ANIMATION_H__

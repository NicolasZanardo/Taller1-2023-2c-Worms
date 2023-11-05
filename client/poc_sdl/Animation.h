/*
 * Created by Federico Manuel Gomez Peter
 * Date: 17/05/18.
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

#include "./frame_selector.h"

#define FRAME_RATE 1000000.0f/25.0f

class SdlTexture;
class Area;

class Animation {
public:
    Animation(SDL2pp::Texture &texture);
    ~Animation();

    void update(float dt);
    void render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dest, SDL_RendererFlip &flipType);

private:
    /** SDL texture of the raw image. */
    SDL2pp::Texture &texture;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed;

    FrameSelector frame_selector;
};

#endif  //__ANIMATION_H__

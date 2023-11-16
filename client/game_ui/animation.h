#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

#include "./frame_selector.h"
#include "sprites_manager.h"

#define FRAME_RATE 1000000.0f/25.0f

class Animation {
public:
    Animation() = delete;
    explicit Animation(SpritesManager& sprites_manager, const std::string& id,
                            FrameSelectorMode mode, uint16_t num_frames, bool img_looking_left);
    ~Animation() = default;

    Animation(Animation&& other);
    Animation& operator=(Animation&& other);

    void reser();
    void update(float dt);
    void render(const SDL2pp::Rect dest, bool facing_left);

private:
    bool img_looking_left;  // Sprite image orientarion.
    float elapsed;  // Time elapsed since last update.
    FrameSelectorMode mode;
    FrameSelector frame_selector;
    SpritesManager* sprites_manager;
    std::string id;
};

#endif  //__ANIMATION_H__

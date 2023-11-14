#ifndef __NON_ANIMATION_H__
#define __NON_ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

#include "frame_selector.h"
#include "sprites_manager.h"

class NonAnimation {
public:
    NonAnimation() = delete;
    explicit NonAnimation(SpritesManager& sprites_manage, const std::string& id, bool img_looking_left);
    ~NonAnimation() = default;

    void render(const SDL2pp::Rect dest, double angle, bool facing_left);

private:
    bool img_looking_left;  // Sprite image orientarion.
    SpritesManager* sprites_manager;
    std::string id;
};

#endif  //__NON_ANIMATION_H__

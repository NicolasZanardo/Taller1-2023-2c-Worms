#ifndef __ICON_H__
#define __ICON_H__

#include <string>

#include "sprites_manager.h"

class Icon {
public:
    Icon() = delete;
    explicit Icon(SpritesManager& sprites_manager, const std::string& id);
    ~Icon() = default;

    void render(const SDL2pp::Rect dest, bool facing_right);

private:
    bool img_looking_left;  // Sprite image orientarion.
    SpritesManager* sprites_manager;
    std::string id;
};

#endif  // __ICON_H__

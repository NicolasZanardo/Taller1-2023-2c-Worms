#ifndef _CLIENT_GAME_DISPLAYABLE_H_
#define _CLIENT_GAME_DISPLAYABLE_H_

#include <SDL2pp/SDL2pp.hh>

class Displayable {
    public:

    virtual void hidden(bool is_hidden) = 0;
    virtual void set_angle(float angle) = 0;
    virtual void set_pos(float x, float y) = 0;
    virtual void image_flipped(bool image_is_flipped) = 0;
    virtual void render(SDL2pp::Renderer& renderer, float delta_time) = 0;
    virtual ~Displayable() {};
};
#endif

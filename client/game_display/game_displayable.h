#ifndef _CLIENT_GAME_DISPLAYABLE_H_
#define _CLIENT_GAME_DISPLAYABLE_H_

#include <SDL2pp/SDL2pp.hh>

class Displayable {
    public:
    virtual void render(SDL2pp::Renderer& renderer, float delta_time) = 0;
    virtual ~Displayable() {};
};
#endif

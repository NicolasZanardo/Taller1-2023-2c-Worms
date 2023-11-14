#ifndef WORM_H
#define WORM_H

#include <SDL2pp/SDL2pp.hh>
#include "../presentation/sdl/Animation.h"
class Worm {
public:
    Worm(SDL2pp::Texture &texture);
    ~Worm();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRight();
    void moveLeft();
    void stopMoving();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};


#endif

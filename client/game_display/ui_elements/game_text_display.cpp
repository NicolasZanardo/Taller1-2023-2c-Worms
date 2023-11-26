#include "game_text_display.h"
#include <SDL_ttf.h>
using namespace SDL2pp;
using namespace std;

GameTextDisplay::GameTextDisplay(
        GameCamera& cam, 
        float x, float y,
        int fnt_size, TextAlign align, TextLayer layer,
        const std::string& text
    ) : cam(cam)
    , transform(x,y,0,0)
    , x(x), y(y)
    , absolute(layer == TextLayer::UI)
    , is_hidden(false)
    , align(align)
    , font("resources/misc/Vera.ttf", fnt_size)
    , surfaceMessage(font.RenderText_Solid(text, SDL_Color{255,255,255,255}))
    { }

void GameTextDisplay::update(const std::string& newval) {
    surfaceMessage = font.RenderText_Solid(newval, SDL_Color{255,255,255,255});
}

void GameTextDisplay::hidden(bool is_hidden) {
    this->is_hidden = is_hidden;
}

void GameTextDisplay::set_pos(float x, float y) {
    this->x = x;
    this->y = y;
}

void GameTextDisplay::render(Renderer& renderer, float delta_time) {
    if (is_hidden)
        return;

    if (!absolute) {
        transform.SetX(cam.transform_x(x));
        transform.SetY(cam.transform_y(y));
    }

    if (texture == nullptr) {
        texture =  make_unique<Texture>(renderer, surfaceMessage);
        transform.SetW(texture->GetWidth());
        transform.SetH(texture->GetHeight());

        if (align == TextAlign::right)
            transform.SetX(transform.GetX()-transform.GetW());
        else if (align == TextAlign::center)
            transform.SetX(transform.GetX()-transform.GetW()/2);
    }

    renderer.Copy(*texture, SDL2pp::NullOpt, transform, 0, SDL2pp::NullOpt, 0);
}

GameTextDisplay::~GameTextDisplay() {}

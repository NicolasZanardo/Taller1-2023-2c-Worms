#include "game_text_display.h"
using namespace SDL2pp;
using namespace std;

GameTextDisplay::GameTextDisplay(
        GameCamera& cam, 
        float x, float y,
        Font* font, TextAlign align, TextLayer layer,
        const string& text,
        SDL2pp::Color color
    ) : cam(cam)
    , transform(x,y,0,0), x(x), y(y), color(color)
    , absolute(layer == TextLayer::UI)
    , is_hidden(false)
    , align(align), font(font)
    , texture(nullptr)
    , surfaceMessage(font->RenderText_Solid(text, color))
    { }

void GameTextDisplay::update(const std::string& newval) {
    surfaceMessage = font->RenderText_Solid(newval, color);

    if (texture != nullptr) {
        delete(texture);
        texture = nullptr;
    }
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

    if (absolute) {
        transform.SetX(x);
        transform.SetY(y);
    } else {
        transform.SetX(cam.transform_x(x));
        transform.SetY(cam.transform_y(y));
    }

    if (texture == nullptr) {
        texture =  new Texture(renderer, surfaceMessage);
        transform.SetW(texture->GetWidth());
        transform.SetH(texture->GetHeight());
        if (align == TextAlign::right)
            transform.SetX(transform.GetX()-transform.GetW());
        else if (align == TextAlign::center)
            transform.SetX(transform.GetX()-transform.GetW()/2);
    }

    renderer.Copy(*texture, SDL2pp::NullOpt, transform, 0, SDL2pp::NullOpt, 0);
}

GameTextDisplay::~GameTextDisplay() {
    delete(texture);
}

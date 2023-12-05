#ifndef _CLIENT_GAME_UI_TEXT_H_
#define _CLIENT_GAME_UI_TEXT_H_

#include <string>
#include <memory>
#include <SDL2pp/SDL2pp.hh>
#include "game_camera.h"
#include "game_displayable.h"

enum TextAlign { left, center, right };
enum TextLayer { UI, ingame };

class GameTextDisplay : public Displayable {
    GameCamera& cam;
    SDL2pp::Rect transform;
    float x,y;
    SDL2pp::Color color;
    bool absolute;
    bool is_hidden;
    TextAlign align;
    SDL2pp::Font* font;
    SDL2pp::Texture* texture;
    SDL2pp::Surface surfaceMessage;

    public:
    ~GameTextDisplay() override;
    explicit GameTextDisplay(GameCamera& cam, float x, float y, SDL2pp::Font* font, TextAlign align, TextLayer layer, const std::string& text, SDL2pp::Color color);

    void update(const std::string& newval);
    void hidden(bool is_hidden);
    void set_pos(float x, float y);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;

    friend class GameTurnDisplayer;
};

#endif
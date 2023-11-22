#ifndef _CLIENT_GAME_UI_TEXT_H_
#define _CLIENT_GAME_UI_TEXT_H_

#include <string>
#include <memory>
#include <SDL2pp/SDL2pp.hh>
#include "game_camera.h"
#include "game_displayable.h"
#include "game_sprite_info.h"


enum class TextAlign : uint8_t {
    left = 0x00,
    center = 0x01,
    right = 0x02
};

class GameUiText : public Displayable {
    GameCamera& cam;
    SDL2pp::Rect transform;
    float x,y;
    bool absolute;
    std::unique_ptr<SDL2pp::Texture> texture;
    std::unique_ptr<SDL2pp::Surface> surfaceMessage;
    bool is_hidden;
    TextAlign align;

    public:
    ~GameUiText() override;
    explicit GameUiText(GameCamera& cam, float x, float y, bool absolute, int fnt_size, TextAlign align, const std::string& text);

    void hidden(bool is_hidden);
    void set_pos(float x, float y);
    void render(SDL2pp::Renderer& renderer, float delta_time) override;
};

#endif
#include "game_display.h"
#include "game_ui/ui_utils.h"
#include "game_sprite.h"

GameDisplay::GameDisplay(Queue<std::shared_ptr<Command>> &command_queue, int fps) :
        fps(fps), sdl(SDL_INIT_VIDEO), ttf(),
        window("Worms",
               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
               UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT,
               SDL_WINDOW_RESIZABLE),
        renderer(window, -1, SDL_RENDERER_ACCELERATED),
        texture_manager(renderer),
        camera(UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT, 30.0f),
        event_handler(window, command_queue)
{
    images.emplace_back(&camera);

    texture_manager.add_texture("wwalk" , "resources/sprites/wwalk.png" , 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("wfall" , "resources/sprites/wfall.png" , 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("wjumpu", "resources/sprites/wjumpu.png", 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("widle" , "resources/sprites/wwalk.png" , 30, 40, 10, 10, 20, 00);
    texture_manager.add_texture("beam_large", "resources/sprites/beam_large.png");
}

GameDisplay::~GameDisplay() {
    for (auto spr: images) {
        delete (spr);
    }
}

void GameDisplay::update(float delta_time) {
    renderer.Clear();
    for (auto spr: images)
        spr->render(renderer, delta_time);
    renderer.Present();
}

GameSprite* GameDisplay::new_sprite(const std::string& spritekey, float width, float height, float angle) {
    GameSprite *sprite = new GameSprite(camera, *texture_manager.get(spritekey));
    sprite->set_size(width, height);
    sprite->set_angle(angle);

    images.emplace_back(sprite);

    return sprite;
}

GameUiText* GameDisplay::new_ui_text(const std::string& text, float x, float y, int fnt_size, TextAlign align) {
    GameUiText *display = new GameUiText(camera, x, y, true, fnt_size, align, text);
    images.emplace_back(display);
    return display;
}

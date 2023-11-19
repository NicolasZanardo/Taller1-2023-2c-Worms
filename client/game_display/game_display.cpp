#include "game_display.h"
#include "game_ui/ui_utils.h"
#include "game_sprite.h"

GameDisplay::GameDisplay(Queue<GameEvent>& event_queue, int fps) :
    fps(fps), sdl(SDL_INIT_VIDEO),
    window("Worms",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE),
    renderer(window, -1, SDL_RENDERER_ACCELERATED),
    texture_manager(renderer),
    event_handler(window, event_queue)
    {
        texture_manager.add_texture("wwalk"     , "resources/sprites/wwalk.png"     ,  60, 60, 0, 28);
        texture_manager.add_texture("wfall"     , "resources/sprites/wfall.png"     ,  60, 60, 0, 28);
        texture_manager.add_texture("wjumpu"    , "resources/sprites/wjumpu.png"    ,  60, 60, 0, 28);
        texture_manager.add_texture("widle"     , "resources/sprites/wwalk.png"     ,  60, 60, 0, 00);
        texture_manager.add_texture("beam_large", "resources/sprites/beam_large.png");//, 140, 20, 0);
    }
GameDisplay::~GameDisplay() {
    for (auto spr: images) {
        delete(spr);
    }
}

void GameDisplay::update(float delta_time) {
    renderer.Clear();
    for (auto spr : images)
        spr->render(renderer, delta_time);
    renderer.Present();
}

Displayable* GameDisplay::new_sprite(const std::string spritekey, float width, float height, float angle) {
    GameSprite* sprite = new GameSprite(*texture_manager.get(spritekey));
    sprite->set_size(width, height);
    sprite->set_angle(angle);

    images.emplace_back(sprite);

    return sprite;
}

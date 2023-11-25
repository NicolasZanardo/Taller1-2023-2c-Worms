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

    // Worms
    texture_manager.add_texture("wwalk" , "resources/sprites/worm/wwalk.png" , 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("wfall" , "resources/sprites/worm/wfall.png" , 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("wjumpu", "resources/sprites/worm/wjumpu.png", 30, 40, 10, 10, 20, 28);
    texture_manager.add_texture("widle" , "resources/sprites/worm/wwalk.png" , 30, 40, 10, 10, 20, 00);
    texture_manager.add_texture("w_bazooka" , "resources/sprites/worm/w_bazooka.png" , 30, 40, 10, 10, 20, 00);
    texture_manager.add_texture("w_green_grenade" , "resources/sprites/worm/w_green_grenade.png" , 30, 40, 10, 10, 20, 00);
    texture_manager.add_texture("w_mortar" , "resources/sprites/worm/w_mortar.png" , 30, 40, 10, 10, 20, 00);

    // Scenario
    texture_manager.add_texture("beam_large", "resources/sprites/scenario/beam_large.png");

    // Projectiles
    texture_manager.add_texture("p_bazooka", "resources/sprites/projectiles/bazooka.png");
    texture_manager.add_texture("p_mortar", "resources/sprites/projectiles/mortar.png");
    texture_manager.add_texture("p_green_grenade", "resources/sprites/projectiles/green_grenade.png");
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

void GameDisplay::remove_sprite(GameSprite *sprite) {
    images.remove_if([sprite](Displayable* displayable) {
        return dynamic_cast<GameSprite*>(displayable) == sprite;
    });

    delete sprite;
}

GameTextDisplay* GameDisplay::new_text(const std::string& text, float x, float y, int fnt_size, TextAlign align, TextLayer layer) {
    GameTextDisplay *display = new GameTextDisplay(camera, x, y, fnt_size, align, layer, text);
    images.emplace_back(display);
    return display;
}




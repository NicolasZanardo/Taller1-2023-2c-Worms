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

    // Scenario
    texture_manager.add_texture("beam_large", "resources/sprites/scenario/beam_large.png");

    int w = 36;
    int h = 36;
    int xoff = 15;
    int yoff = 11;
    int sep = 60-h;

    // Worms
    texture_manager.add_texture("wwalk"           , "resources/sprites/worm/wwalk.png"          ,w,h,xoff,yoff-2,sep, SpriteAnimationType::LOOP   , 28);
    texture_manager.add_texture("wfall"           , "resources/sprites/worm/wfall.png"          ,w,h,xoff,yoff  ,sep, SpriteAnimationType::FREEZE , 28);
    texture_manager.add_texture("wjumpu"          , "resources/sprites/worm/wjumpu.png"         ,w,h,xoff,yoff  ,sep, SpriteAnimationType::REVERSE, 28);
    texture_manager.add_texture("widle"           , "resources/sprites/worm/wwalk.png"          ,w,h,xoff,yoff-2,sep, SpriteAnimationType::NONE   , 28);
    // Aiming
    texture_manager.add_texture("w_bazooka"       , "resources/sprites/worm/w_bazooka.png"      ,w,h,xoff,yoff-2,sep, SpriteAnimationType::BY_ANGLE, 28);
    texture_manager.add_texture("w_mortar"        , "resources/sprites/worm/w_mortar.png"       ,w,h,xoff,yoff-2,sep, SpriteAnimationType::BY_ANGLE, 28);
    texture_manager.add_texture("w_green_grenade" , "resources/sprites/worm/w_green_grenade.png",w,h,xoff,yoff-2,sep, SpriteAnimationType::FREEZE  , 28);
    // Projectiles
    texture_manager.add_texture("p_bazooka"       , "resources/sprites/projectiles/bazooka.png"      ,w,h,xoff,yoff,sep, SpriteAnimationType::BY_ANGLE, 0);
    texture_manager.add_texture("p_mortar"        , "resources/sprites/projectiles/mortar.png"       ,w,h,xoff,yoff,sep, SpriteAnimationType::BY_ANGLE, 0);
    texture_manager.add_texture("p_green_grenade" , "resources/sprites/projectiles/green_grenade.png",w,h,xoff,yoff,sep, SpriteAnimationType::BY_ANGLE, 0);
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

void GameDisplay::remove(Displayable* item) {
    images.remove_if([item](Displayable* displayable) {
        return displayable == item;
    });

    delete item;
}

GameSprite* GameDisplay::new_sprite(const std::string& spritekey, float width, float height, float angle) {
    GameSprite *sprite = new GameSprite(camera, *texture_manager.get(spritekey), width, height, angle);

    images.emplace_back(sprite);

    return sprite;
}

GameTextDisplay* GameDisplay::new_text(const std::string& text, float x, float y, int fnt_size, TextAlign align, TextLayer layer) {
    GameTextDisplay *display = new GameTextDisplay(camera, x, y, fnt_size, align, layer, text);
    images.emplace_back(display);
    return display;
}

WormAnimationSet* GameDisplay::new_worm_animation(float size_scale, float angle) {
    WormAnimationSet* animset = new WormAnimationSet(
        new GameSprite(camera, *texture_manager.get("widle") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *texture_manager.get("wwalk") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *texture_manager.get("wjumpu"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *texture_manager.get("wfall") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),

        new GameSprite(camera, *texture_manager.get("w_bazooka")      , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *texture_manager.get("w_mortar")       , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *texture_manager.get("w_green_grenade"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle)
    );

    images.emplace_back(animset);
    return animset;
}

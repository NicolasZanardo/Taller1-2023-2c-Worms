#include "game_display.h"
#include "game/utils_constants.h"
#include "game_sprite.h"
#include "sprite_animation.h"

GameDisplay::GameDisplay(Queue<std::shared_ptr<Command>> &command_queue, int fps)
        : fps(fps)
        , sdl(SDL_INIT_VIDEO)
        , ttf()
        , window("Worms",
               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
               UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT,
               SDL_WINDOW_RESIZABLE)
        , renderer(window, -1, SDL_RENDERER_ACCELERATED)
        , resources(renderer)
        , camera(UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT, 30.0f)
        , event_handler(window, command_queue)
{
    // UI
    resources.add_texture("ui_bazooka"      , "resources/weapon_icons/bazooka.png");
    resources.add_texture("ui_mortar"       , "resources/weapon_icons/mortar.png");
    resources.add_texture("ui_green_grenade", "resources/weapon_icons/green_grenade.png");
    resources.add_texture("ui_hgrenade", "resources/weapon_icons/hgrenade.png");
    resources.add_texture("ui_dynamite", "resources/weapon_icons/dynamite.png");

    resources.add_texture("explosion", "resources/sprites/effects/circle50.png",100,100,0,0,0,SpriteAnimationType::FREEZE,28);

    // Scenario
    resources.add_texture("beam_large", "resources/sprites/scenario/beam_large.png");
    resources.add_texture("fondo", "resources/sprites/scenario/fondo.png");
    resources.add_texture("underwater_film", "resources/sprites/scenario/underwater_film.png");
    resources.add_texture("water_line", "resources/sprites/scenario/water_line.png", 128,24,0,0,0,SpriteAnimationType::LOOP, 14);

    int w = 36;
    int h = 36;
    int xoff = 15;
    int yoff = 11;
    int sep = 60-h;

    // Worms
    resources.add_texture("wwalk"           , "resources/sprites/worm/wwalk.png"          ,w,h,xoff,yoff-2 ,sep, SpriteAnimationType::LOOP   , 28);
    resources.add_texture("wfall"           , "resources/sprites/worm/wfall.png"          ,w,h,xoff,yoff   ,sep, SpriteAnimationType::FREEZE , 28);
    resources.add_texture("wjumpu"          , "resources/sprites/worm/wjumpu.png"         ,w,h,xoff,yoff   ,sep, SpriteAnimationType::FREEZE , 28);
    resources.add_texture("widle"           , "resources/sprites/worm/wwalk.png"          ,w,h,xoff,yoff-2 ,sep, SpriteAnimationType::NONE   , 28);
    resources.add_texture("wdead"           , "resources/sprites/worm/grave1.png"         ,w,h,xoff,yoff-10,sep, SpriteAnimationType::REVERSE, 28);
    // Aiming
    resources.add_texture("w_bazooka"       , "resources/sprites/worm/w_bazooka.png"      ,w,h,xoff,yoff-2,sep, 90,-180);
    resources.add_texture("w_mortar"        , "resources/sprites/worm/w_mortar.png"       ,w,h,xoff,yoff-2,sep, 90,-180);
    resources.add_texture("w_green_grenade" , "resources/sprites/worm/w_green_grenade.png",w,h,xoff,yoff-2,sep, SpriteAnimationType::FREEZE  , 28);
    resources.add_texture("w_hgrenade" , "resources/sprites/worm/w_hgrenade.png",w,h,xoff,yoff-2,sep, SpriteAnimationType::FREEZE  , 28);
    resources.add_texture("w_dynamite" , "resources/sprites/worm/w_dynamite.png",w,h,xoff,yoff-2,sep, SpriteAnimationType::FREEZE  , 28);
    // Projectiles
    resources.add_texture("p_bazooka"       , "resources/sprites/projectiles/bazooka.png"      ,w,h,xoff,yoff,sep, 90,360);
    resources.add_texture("p_mortar"        , "resources/sprites/projectiles/mortar.png"       ,w,h,xoff,yoff,sep, 90,360);
    resources.add_texture("p_green_grenade" , "resources/sprites/projectiles/green_grenade.png",w,h,xoff,yoff,sep, 90,360);
    resources.add_texture("p_clustlet"      , "resources/sprites/projectiles/clustlet.png"     ,w,h,xoff,yoff,sep, 90,360);
    resources.add_texture("p_hgrenade"      , "resources/sprites/projectiles/hgrenade.png"     ,w,h,xoff,yoff,sep, 90,360);
    resources.add_texture("p_dynamite"      , "resources/sprites/projectiles/dynamite.png"     ,w,h,xoff,yoff,sep, 90,360);
}

void GameDisplay::update(float delta_time) {
    clean_removed_sprites();

    camera.render(renderer, delta_time);
    renderer.Clear();
        for (const auto& ptr : images) {
            ptr->render(renderer, delta_time);
        }

        for (const auto& ptr : foreground) {
            ptr->render(renderer, delta_time);
        }

        for (const auto& ptr : user_interface) {
            ptr->render(renderer, delta_time);
        }
    renderer.Present();

    clean_removed_sprites();
}

void GameDisplay::remove(Displayable* item) {
    toremove.emplace_back(item);
}
void GameDisplay::clean_removed_sprites() {
    for (auto item : toremove) {
        images.remove_if([item](const auto& displayable) {
            return displayable.get() == item;
        });

        foreground.remove_if([item](const auto& displayable) {
            return displayable.get() == item;
        });

        user_interface.remove_if([item](const auto& displayable) {
            return displayable.get() == item;
        });
    }
    toremove.clear();
}


GameSprite* GameDisplay::new_sprite(const std::string& spritekey, float width, float height, float angle) {
    GameSprite *sprite = new GameSprite(camera, *resources.get_sprite(spritekey), width, height, angle);
    images.emplace_back(sprite);
    return sprite;
}

GameTextDisplay* GameDisplay::new_text(const std::string& text, float x, float y, TextAlign align, TextLayer layer, TextType type, int color) {
    uint8_t* prt = (uint8_t*)&color;
    SDL2pp::Color txtcolor{*(prt+2), *(prt+1), *(prt+0), 255 };
    GameTextDisplay *display = new GameTextDisplay(camera, x, y, resources.get_font(type), align, layer, text, txtcolor);
    user_interface.emplace_back(display);
    return display;
}

WormAnimationSet* GameDisplay::new_worm_animation(float size_scale, float angle) {
    WormAnimationSet* animset = new WormAnimationSet(
        new GameSprite(camera, *resources.get_sprite("widle") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("wwalk") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("wjumpu"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("wfall") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("wdead") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("wfall") , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),

        new GameSprite(camera, *resources.get_sprite("w_bazooka")      , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("w_mortar")       , WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("w_green_grenade"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("w_hgrenade"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle),
        new GameSprite(camera, *resources.get_sprite("w_dynamite"), WORM_SIZE*size_scale, WORM_SIZE*size_scale, angle)
    );

    images.emplace_back(animset);
    return animset;
}


void GameDisplay::start_scenario(float width, float height, float water_level) {
    camera.set_bounds(width, height);
    float gameW = camera.px_to_w(128);
    float gameH = camera.px_to_h(24);


    GameSprite *background = new GameSprite(camera, *resources.get_sprite("fondo"), width, height, 0.0);
    background->set_pos(width/2, water_level - gameH/2);
    images.emplace_back(background);

    for (float i = 0.0f; i < width; i += gameW) {
        GameSprite *sprite = new GameSprite(camera, *resources.get_sprite("water_line"), gameW, gameH, 0.0);
        sprite->set_pos(i+gameW/2, water_level-gameH/2);
        foreground.emplace_back(sprite);
    }
    GameSprite *layer = new GameSprite(camera, *resources.get_sprite("underwater_film"), width, height-water_level-gameH, 0.0);
    layer->set_pos(width/2,water_level-gameH-((height-water_level-gameH)/2));
    foreground.emplace_back(layer); 

    Displayable* overlay[] {
        new GameSprite(*resources.get_sprite("ui_bazooka"), 32, 32, 0),
        new GameSprite(*resources.get_sprite("ui_mortar"), 32, 32, 0),
        new GameSprite(*resources.get_sprite("ui_green_grenade"), 32, 32, 0),
        new GameSprite(*resources.get_sprite("ui_hgrenade"), 32, 32, 0),
        new GameSprite(*resources.get_sprite("ui_dynamite"), 32, 32, 0),
        new GameTextDisplay(camera, 0, 32, resources.get_font(TextType::title), TextAlign::left, TextLayer::UI, "Q  W  E   R  F", {255,255,255,255})
    };

    for (auto it : overlay)
        foreground.emplace_back(it);

    ((GameSprite*)overlay[1])->set_pos(42,0);
    ((GameSprite*)overlay[2])->set_pos(88,0);
    ((GameSprite*)overlay[3])->set_pos(134,0);
    ((GameSprite*)overlay[4])->set_pos(180,0);
}

void GameDisplay::new_vfx(const std::string& spritekey, float x, float y, float width, float height, float angle) {
    auto& info = *resources.get_sprite(spritekey);

    GameSprite *sprite = new GameSprite(camera, info, width, height, angle);
    sprite->set_pos(x,y);

    auto vfx = new VFXAnimation(info);
    sprite->animation = std::unique_ptr<SpriteAnimation>(vfx);
    vfx->setup(*this, *sprite);

    images.emplace_back(sprite);
}

void GameDisplay::clear_screen() {
    //images.clear();
    foreground.clear();
    user_interface.clear();
}

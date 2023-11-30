#ifndef _CLIENT_GAME_DISPLAY_H_
#define _CLIENT_GAME_DISPLAY_H_

#include <list>
#include <string>
#include <SDL2pp/SDL2pp.hh>
#include "queue.h"
#include "game_camera.h"
#include "event_handler.h"
#include "game_resources_manager.h"
#include "game_displayable.h"
#include "game_sprite.h"
#include "Game/GameAction.h"
#include "game_text_display.h"
#include "game_worm_animation_set.h"

class GameDisplay {
    int fps;
    SDL2pp::SDL sdl;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    ResourceManager resources;
    std::list<Displayable*> images;
    std::list<Displayable*> foreground;
    std::list<Displayable*> user_interface;
    public:
    GameCamera camera;
    EventHandler event_handler;
    GameDisplay(Queue<std::shared_ptr<Command>> &command_queue, int fps);
    ~GameDisplay();

    void update(float delta_time);
    void remove(Displayable* item);
    void start_scenario(float width, float height, float water_level);
    WormAnimationSet* new_worm_animation(float size_scale, float angle);
    GameTextDisplay* new_text(const std::string& text, float x, float y, TextAlign align, TextLayer layer, TextType type);
    GameSprite* new_sprite(const std::string& spritekey, float width, float height, float angle = 0);
};

#endif

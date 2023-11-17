#include "client.h"

#include <cmath>
#include <chrono>
#include <thread>

#include "client_game_state.h"
#include "event_handler.h"
#include "game_loop.h"
#include "sprite.h"
#include "sprites_manager.h"

Client::Client(const char* host_name, const char* service_name)
    : channel(host_name, service_name)
    , receiver(state_queue, channel)
    , sender(event_queue, channel) {}

void Client::execute() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Worms",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        UiUtils::WINDOW_WIDTH, UiUtils::WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    EventHandler event_handler(window, event_queue);

    SpritesManager sprites_manager(renderer);
    sprites_manager.addSprite("wwalk", "resources/sprites/wwalk.png", 60, 60, 0);
    sprites_manager.addSprite("wfall", "resources/sprites/wfall.png", 60, 60, 0);
    sprites_manager.addSprite("beam_large", "resources/sprites/beam_large.png", 140, 20, 0);

    ClientGameState game_state(sprites_manager);

    this->receiver.start();
    this->sender.start();

    GameLoop game_loop(renderer, this->state_queue);
    game_loop.execute(event_handler, game_state);

    this->event_queue.close();
    this->echo_queue.close();
    this->state_queue.close();

    this->receiver.join();
    // this->sender.join();
}

#include "client.h"

#include <cmath>
#include <chrono>
#include <thread>

#include "game_loop.h"
#include "Player.h"
#include "./sprite.h"

Client::Client(const char* host_name, const char* service_name)
    : receiver(state_queue, echo_queue)
    , sender(event_queue, echo_queue)
    , event_handler(event_queue) {}

void Client::execute() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Worms",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600,
        SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    Sprite sprite(renderer);
    Player player(sprite);

    this->receiver.start();
    this->sender.start();

    GameLoop game_loop(renderer, this->state_queue);
    game_loop.execute(event_handler, player);

    this->event_queue.close();
    this->echo_queue.close();
    this->state_queue.close();

    this->receiver.join();
    this->sender.join();
}

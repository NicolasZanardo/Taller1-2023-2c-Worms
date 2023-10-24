#include "client.h"

#include <iostream>

Client::Client(const char* host_name, const char* service_name) {}

void Client::execute() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Texture im(renderer,
                       SDL2pp::Surface("resources/sprites/wwalk.png").SetColorKey(true, 0));

    Worm worm(im);
    bool running = true;
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
    while (running) {
        running = handleEvents(player);
        update(player, FRAME_RATE);
        render(renderer, player);
        // la cantidad de segundos que debo dormir se debe ajustar en función
        // de la cantidad de tiempo que demoró el handleEvents y el render
        usleep(FRAME_RATE);
    }
}


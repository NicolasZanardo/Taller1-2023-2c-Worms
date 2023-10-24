#include "client.h"

#include <iostream>

// TODO Move functions
static void render(SDL2pp::Renderer &renderer, Worm &worm);
static void update(Worm &worm, float dt);

Client::Client(const char* host_name, const char* service_name): eventHandler() {}

void Client::execute() { // TODO Move game loop
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Texture texture(renderer,
                       SDL2pp::Surface("resources/sprites/wwalk.png").SetColorKey(true, 0));

    Worm worm(texture);
    bool running = true;
    // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
    // del update del modelo.
    while (running) {
        running = handleEvents(worm);
        update(worm, FRAME_RATE);
        render(renderer, worm);
        usleep(FRAME_RATE);
    }
}

bool Client::handleEvents(Worm& worm) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while(SDL_PollEvent(&event)) {
        Command* command = eventHandler.handleEvent(event);
        if (command) {
            command->execute(worm);
        }
    }
}

static void render(SDL2pp::Renderer &renderer, Worm &worm) {
    renderer.Clear();
    worm.render(renderer);
    renderer.Present();
}

static void update(worm &worm, float dt) {
    worm.update(dt);
}
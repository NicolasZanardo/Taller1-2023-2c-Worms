#include "client.h"

// TODO Move functions
static void render(SDL2pp::Renderer &renderer, Worm &worm);
static void update(Worm &worm, float dt);

Client::Client(const char* host_name, const char* service_name): eventHandler() {}

void Client::execute() { // TODO Move game loop
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                          800, 600, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL2pp::Surface surface = SDL2pp::Surface("sprites/wwalk.png");
    SDL2pp::Texture texture(renderer,
                       surface);

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
        if (event.type == SDL_QUIT) {
            std::cout << "Quit" << std::endl;
            return false;
        }
        Command* command = eventHandler.handleEvent(event);
        if (command) {
            command->execute(worm);
        }
    }
    return true;
}

static void render(SDL2pp::Renderer &renderer, Worm &worm) {
    renderer.Clear();
    worm.render(renderer);
    renderer.Present();
}

static void update(Worm &worm, float dt) {
    worm.update(dt);
}
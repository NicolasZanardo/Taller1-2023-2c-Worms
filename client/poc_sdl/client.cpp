#include "client.h"

#include <cmath>
#include <chrono>
#include <thread>

#include "Player.h"

Client::Client(const char* host_name, const char* service_name)
    : receiver(state_queue, echo_queue)
    , sender(event_queue, echo_queue)
    , event_handler(event_queue) {}

void Client::execute() {
    using namespace std::chrono;

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_RESIZABLE);

    SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL2pp::Texture im(renderer, 
        SDL2pp::Surface("assets/soldier2.png").SetColorKey(true, 0));

    Player player(im);
    bool running = true;

    this->receiver.start();
    this->sender.start();

    time_point t1 = steady_clock::now();
	microseconds frame_rate(1000000 / 25);
    double it = FRAME_RATE;
    double it_prev = 0;

    while (running) {
        running = this->event_handler.handleEvents();
        double dt = it - it_prev;
        this->update(player, dt);
        this->render(renderer, player);

        it_prev = it;
        time_point t2 = steady_clock::now();
        microseconds rest = frame_rate - duration_cast<microseconds>(t2 - t1);
        if (rest.count() < 0) {
            microseconds behind = -rest;
            microseconds lost = behind - (behind % frame_rate);
            t1 += lost;
            it += lost.count() / frame_rate.count();
        } else {
            std::this_thread::sleep_for(rest);
        }

        t1 += frame_rate;
        it += FRAME_RATE;
    }

    this->event_queue.close();
    this->echo_queue.close();
    this->state_queue.close();

    this->receiver.join();
    this->sender.join();
}

void Client::update(Player &player, float dt) {
    GameEvent event;

    while(this->state_queue.try_pop(event)) {
        switch(static_cast<uint8_t>(event)) {
            case static_cast<uint8_t>(GameEvent::MOVE_LEFT_INIT): {
                player.moveLeft();
                break;
            }
            case static_cast<uint8_t>(GameEvent::MOVE_RIGHT_INIT): {
                player.moveRigth();
                break;
            }
            case static_cast<uint8_t>(GameEvent::MOVE_LEFT_END): {
                player.stopMoving();
                break;
            }
            case static_cast<uint8_t>(GameEvent::MOVE_RIGHT_END): {
                player.stopMoving();
                break;
            }
            default:
                break;
        }
    }

    player.update(dt);
}

void Client::render(SDL2pp::Renderer &renderer, Player &player) {
    renderer.Clear();
    player.render(renderer);
    renderer.Present();
}

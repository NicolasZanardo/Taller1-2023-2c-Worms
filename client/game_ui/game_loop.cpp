#include "./game_loop.h"

#include <chrono>
#include <thread>

// GameLoop::GameLoop(SDL2pp::Renderer& renderer, Queue<GameEvent>& state_queue)
//     : renderer(&renderer)
//     , state_queue(&state_queue) {}

GameLoop::GameLoop(SDL2pp::Renderer& renderer, Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue)
    : renderer(&renderer)
    , state_queue(&state_queue)
    , game_state_was_initialized(false) {}

void GameLoop::execute(EventHandler& event_handler, ClientGameState& game_state) {
    using namespace std::chrono;

    bool running = true;

    time_point t1 = steady_clock::now();
	microseconds frame_rate(1000000 / 25);
    double it = FRAME_RATE;
    double it_prev = 0;

    while (running) {        
        running = event_handler.handleEvents();
        double dt = it - it_prev;
        this->update(game_state, dt);
        std::cout << "init render phase\n";
        this->render(game_state);
        std::cout << "end renader phase\n";

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
}

void GameLoop::update(ClientGameState &game_state, float dt) {
    std::shared_ptr<ClientGameStateDTO> game_state_dto;

    if (this->game_state_was_initialized == false) {
        std::cout << "Inicializando estado del juego.\n";
        this->state_queue->try_pop(game_state_dto);
        if (game_state_dto == nullptr) {
            return;
        }
        game_state.load(game_state_dto);
        this->game_state_was_initialized = true;
    } else {
        bool receive_new_state = false;
        while (this->state_queue->try_pop(game_state_dto)) {
            receive_new_state = true;
        }
        if (receive_new_state) {
            std::cout << "Actualizando estado del juego.\n";
            game_state.update(game_state_dto, dt);
        }
    }

    // bool receive_new_state = false;
    // while(this->state_queue->try_pop(game_state_dto)) {
    //     receive_new_state = true;
    // }

    // if (receive_new_state) {
    //     std::cout << "w: " << game_state_dto->width << " - h: " << game_state_dto->height << '\n';

    //     if (this->game_state_was_initialized == false) {
    //         game_state.load(game_state_dto);
    //         this->game_state_was_initialized = true;
    //     } else {
    //         game_state.update(game_state_dto, dt);
    //     }
    // }
}

void GameLoop::render(ClientGameState &game_state) {
    this->renderer->Clear();
    game_state.render();
    this->renderer->Present();
}

#include "./game_loop.h"

#include <chrono>
#include <thread>

GameLoop::GameLoop(SDL2pp::Renderer& renderer, Queue<GameEvent>& state_queue)
    : renderer(&renderer)
    , state_queue(&state_queue) {}

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
        this->render(game_state);

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
    std::unique_ptr<ClientGameStateDTO> game_state_dto;

    bool receive_new_state = false;
    while(this->state_queue->try_pop(game_state_dto)) {
        receive_new_state = true;
    }

    if (receive_new_state) {
        game_state.update(dt, game_state_dto);
    }
}

void GameLoop::render(ClientGameState &game_state) {
    this->renderer->Clear();
    game_state.render();
    this->renderer->Present();
}

#include "game_loop.h"
#include "game_clock.h"

GameLoop::GameLoop(GameDisplay& display, Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue)
    : display(display), state_queue(state_queue), game_state_was_initialized(false) 
    { }

void GameLoop::execute(EventHandler& event_handler, ClientGameState& game_state) {
    bool running = true;
    GameClock clock(CLIENT_FPS);

    while (running) {     
        running = event_handler.handleEvents();
        update(game_state);
        display.update(clock.delta());
        clock.sync();
    }
}

void GameLoop::update(ClientGameState &game_state) {
    std::shared_ptr<ClientGameStateDTO> game_state_dto;
    if (game_state_was_initialized == false) {
        //std::cout << "Inicializando estado del juego.\n";
        state_queue.try_pop(game_state_dto);
        if (game_state_dto == nullptr) {
            return;
        }
        game_state.load(game_state_dto);
        game_state_was_initialized = true;
    } else {
        bool receive_new_state = false;
        while (state_queue.try_pop(game_state_dto)) {
            receive_new_state = true;
        }
        if (receive_new_state) {
            game_state.update(game_state_dto);
        }
    }
}

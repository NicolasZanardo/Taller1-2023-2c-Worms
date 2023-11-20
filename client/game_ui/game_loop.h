#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include <memory>

#include "queue.h"
#include "game_display.h"
#include "event_handler.h"
#include "client_game_state.h"

class GameLoop {
public:
    GameLoop() = delete;
    explicit GameLoop(GameDisplay& display, Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue);
    ~GameLoop() = default;

    void execute(EventHandler& event_handler, ClientGameState& player);

private:
    GameDisplay &display;
    Queue<std::shared_ptr<ClientGameStateDTO>> &state_queue;
    bool game_state_was_initialized;

    Displayable* spr; float x;
    void update(ClientGameState &game_state);
};

#endif // __GAME_LOOP_H__

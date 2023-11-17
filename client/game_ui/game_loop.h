#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "queue.h"

#include "event_handler.h"
#include "client_game_state.h"

class GameLoop {
public:
    GameLoop() = delete;
    // explicit GameLoop(SDL2pp::Renderer& renderer, Queue<GameEvent>& state_queue);
    explicit GameLoop(SDL2pp::Renderer& renderer, Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue);
    ~GameLoop() = default;

    void execute(EventHandler& event_handler, ClientGameState& player);

private:
    void update(ClientGameState &game_state, float dt);
    void render(ClientGameState &game_state);

    SDL2pp::Renderer* renderer;
    // Queue<GameEvent>* state_queue;
    Queue<std::shared_ptr<ClientGameStateDTO>>& state_queue;
};

#endif  // __GAME_LOOP_H__

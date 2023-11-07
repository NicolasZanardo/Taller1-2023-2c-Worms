#ifndef __GAME_LOOP_H__
#define __GAME_LOOP_H__

#include <SDL2pp/SDL2pp.hh>

#include "queue.h"

#include "event_handler.h"
#include "player_state.h"

class GameLoop {
public:
    GameLoop() = delete;
    explicit GameLoop(SDL2pp::Renderer& renderer, Queue<GameEvent>& state_queue);
    ~GameLoop() = default;

    void execute(EventHandler& event_handler, PlayerState& player);

private:
    void update(PlayerState &player, float dt);
    void render(PlayerState &player);

    SDL2pp::Renderer* renderer;
    Queue<GameEvent>* state_queue;
};

#endif  // __GAME_LOOP_H__

#ifndef __CLIENT_EVENT_HANDLER__
#define __CLIENT_EVENT_HANDLER__

#include <SDL2pp/SDL2pp.hh>

#include "cursor.h"

#include "queue.h"
#include "Game/GameAction.h"
#include "commands/Command.h"

class Player;
typedef Queue<std::shared_ptr<Command>>& CommandQueue;

class EventHandler {
public:
    EventHandler() = delete;
    explicit EventHandler(SDL2pp::Window& window_ref, CommandQueue command_queue);
    ~EventHandler() = default;

    bool handleEvents();

private:
    SDL2pp::Window* window;
    Cursor cursor;
    CommandQueue command_queue;
};


#endif  // __CLIENT_EVENT_HANDLER__

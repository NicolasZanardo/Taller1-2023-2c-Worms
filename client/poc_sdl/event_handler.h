#ifndef __CLIENT_EVENT_HANDLER__
#define __CLIENT_EVENT_HANDLER__

#include <SDL2pp/SDL2pp.hh>

#include "client_defs.h"
#include "cursor.h"

#include "queue.h"

class Player;

class EventHandler {
public:
    EventHandler() = delete;
    explicit EventHandler(SDL2pp::Window& window_ref, Queue<GameEvent>& event_queue);
    ~EventHandler() = default;

    bool handleEvents();

private:
    SDL2pp::Window* window;
    Cursor cursor;
    Queue<GameEvent>& event_queue;
};


#endif  // __CLIENT_EVENT_HANDLER__

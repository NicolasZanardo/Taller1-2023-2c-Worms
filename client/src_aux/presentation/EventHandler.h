#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>

#include "../../../common_base/queue.h"
#include "commands/Commands.h"

enum GameEvent {
    INVALID_EV = 0,
    JUMPING_EV,
    MOVING_RIGHT_EV,
    MOVING_LEFT_EV,
    STOP_MOVING_EV,
    EXIT_EV
};

enum Key {
    UNMAPPED_KEY = 0,
    UP_KEY,
    LEFT_KEY,
    RIGHT_KEY
};

class EventHandler {
public:
    EventHandler();
    ~EventHandler();

    Command* handleEvent(const SDL_Event& e);
    bool isPressed(int button) const;

private:
    std::unordered_map<SDL_Keycode, Key> keys;
    std::unordered_map<GameEvent, Command*> eventToCommandMap; //TODO Use shared_pointer?
    Key key_pressed = UNMAPPED_KEY;

    // Queue<Command*>& commands;

    void _bindKeycodes();
    Key _getKey(const SDL_Keycode& key);
    GameEvent _getEvent(const SDL_Event& e);
    GameEvent _getKeyDownEv(const SDL_Event& e);
    GameEvent _getKeyUpEv(const SDL_Event& e);
};


#endif

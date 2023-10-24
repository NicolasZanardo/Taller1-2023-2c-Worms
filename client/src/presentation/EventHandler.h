#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <string> // TODO DELETE
#include "commands/command.h"

enum Key {
    UNMAPPED_KEY = 0,
    UP_KEY,
    DOWN_KEY,
    LEFT_KEY,
    RIGHT_KEY,
    ENTER_KEY,
    GRAB_THROW_KEY,
    DELETE_KEY,
    ESC_KEY,
    COMMAND_KEY,
    PM_KEY
};

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    void handleInput(string sdlEvent); // TODO Change to SDL EVENT
    bool isPressed(int button) const;
    void _bindKeycodes();

private:
    std::unordered_map<SDL_Keycode, Key> keys;
    Key key_pressed = UNMAPPED_KEY;
    Command* leftKey;
    Command* rightKey;
    Command* upKey;
    Command* downKey;
};


#endif

#include "InputHandler.h"

InputHandler::InputHandler() {

}

InputHandler::~InputHandler() {

}

void InputHandler::handleInput(string sdlEvent) {
    switch(sdlEvent) {
        case "leftKey": {
            leftKey->execute()
        } case "upKey": {
            upKey->execute()
        }
        case "rightKey": {
            rightKey->execute()
        }
        case "upKey": {
            upKey->execute()
        }
    }
}

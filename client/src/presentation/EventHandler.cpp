#include "EventHandler.h"

EventHandler::EventHandler() {
    _bindKeycodes();
}

EventHandler::~EventHandler() {

}

Command *EventHandler::handleEvent(const SDL_Event &e) {
    GameEvent event = _getEvent(e);

    switch (event) {
        case INVALID_EV: {
            break;
        }
        case JUMPING_EV: {
            return new JumpCommand();
        }
        case MOVING_RIGHT_EV: {
            return new MoveCommand(MovingDirection::RIGHT);
        }
        case MOVING_LEFT_EV: {
            return new MoveCommand(MovingDirection::LEFT);
        }
        case STOP_MOVING_EV: {
            return new StopMovingCommand();
        }
        case EXIT_EV: {
            return NULL; // TODO?
        }
    }
    return NULL;
}

Key EventHandler::_getKey(const SDL_Keycode &key) {
    if (keys.count(key)) {
        return keys.at(key);
    }

    return UNMAPPED_KEY;
}

GameEvent EventHandler::_getEvent(const SDL_Event &e) {
    switch (e.type) {
        case SDL_QUIT: {
            std::cout << "Quit" << std::endl;
            return EXIT_EV;
        }

        case SDL_KEYDOWN: {
            std::cout << "Key down" << std::endl;
            return _getKeyDownEv(e);
        }

        case SDL_KEYUP: {
            std::cout << "Key up" << std::endl;
            return _getKeyUpEv(e);
        }

        case SDL_MOUSEMOTION: {
            std::cout << "Oh! Mouse" << std::endl;
            return INVALID_EV;
        }
        default: {
            std::cout << "Default" << std::endl;
            return INVALID_EV;
        }
    }
}

GameEvent EventHandler::_getKeyDownEv(const SDL_Event &e) {
    Key key = _getKey(e.key.keysym.sym);

    if (key == UNMAPPED_KEY) {
        return INVALID_EV;
    }

    switch (key) {
        case UP_KEY: {
            return JUMPING_EV;
        }

        case LEFT_KEY: {
            return MOVING_LEFT_EV;
        }

        case RIGHT_KEY: {
            return MOVING_RIGHT_EV;
        }

        default: {
            break;
        }
    }
}

GameEvent EventHandler::_getKeyUpEv(const SDL_Event &e) {
    Key key = _getKey(e.key.keysym.sym);

    switch (key) {
        case UNMAPPED_KEY:
            break;

        case UP_KEY:
        case LEFT_KEY:
        case RIGHT_KEY:
            return STOP_MOVING_EV;

        default:
            break;
    }

    return INVALID_EV;
}

void EventHandler::_bindKeycodes() {
    keys.emplace(SDLK_w, UP_KEY);
    keys.emplace(SDLK_a, LEFT_KEY);
    keys.emplace(SDLK_d, RIGHT_KEY);
}
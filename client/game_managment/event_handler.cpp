#include "event_handler.h"

#include "client_game_state.h"
#include <iostream>

EventHandler::EventHandler(SDL2pp::Window& window_ref, Queue<GameEvent>& event_queue)
    : window(&window_ref)
    , cursor(window->GetWidth(), window->GetHeight(), 1000, 1000)
    , event_queue(event_queue) {}

bool EventHandler::handleEvents() {
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        this->event_queue.push(GameEvent::MOVE_LEFT_INIT);
                        break;
                    case SDLK_RIGHT:
                        this->event_queue.push(GameEvent::MOVE_RIGHT_INIT);
                        break;
                    case SDLK_RETURN:
                        this->event_queue.push(GameEvent::JUMP_FORWARD);
                        break;
                    case SDLK_SPACE:
                        this->event_queue.push(GameEvent::JUMP_BACKWARDS);
                        break;
                    case SDLK_UP:
                        this->event_queue.push(GameEvent::AIM_UP_INIT);
                        break;
                    case SDLK_DOWN:
                        this->event_queue.push(GameEvent::AIM_DOWN_INIT);
                        break;
                    case SDLK_DELETE: // todo change then
                        this->event_queue.push(GameEvent::SHOOT);
                        break;
                    }
                }
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        this->event_queue.push(GameEvent::MOVE_LEFT_END);
                        break;
                    case SDLK_RIGHT:
                        this->event_queue.push(GameEvent::MOVE_RIGHT_END);
                        break;
                    case SDLK_UP:
                        this->event_queue.push(GameEvent::AIM_UP_STOPPED);
                        break;
                    case SDLK_DOWN:
                        this->event_queue.push(GameEvent::AIM_DOWN_STOPPED);
                        break;
                    } 
                }
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
            default:
                break;    
        }
    }

    return true;
}

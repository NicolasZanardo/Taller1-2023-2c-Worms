#include "event_handler.h"

#include "player_state.h"

EventHandler::EventHandler(Queue<GameEvent>& event_queue)
    : event_queue(event_queue) {}

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
                    } 
                }
                break;
            case SDL_MOUSEMOTION:
                std::cout << "Oh! Mouse" << std::endl;
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

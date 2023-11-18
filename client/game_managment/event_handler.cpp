#include "event_handler.h"

#include "client_game_state.h"

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
                // std::cout << "Oh! Mouse" << std::endl;

                // SDL_GetMouseState(&x, &y);
                // std::cout << "x: " << cursor.getPosX() << " - y: " << cursor.getPosY() << '\n';
                // std::cout << "xn: " << cursor.getNormPosX() << " - yn: " << cursor.getNormPosY() << '\n';
                // std::cout << "W: " << this->window->GetWidth() << " - H: " << this->window->GetHeight() << '\n';
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

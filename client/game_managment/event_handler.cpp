#include "event_handler.h"
#include "commands/GameActionCommand.h"
#include "commands/ChangeWeaponCommand.h"
#include "commands/ChangeProjectileCountDownCommand.h"
#include "commands/ToggleCheatCommand.h"

#include <iostream>

EventHandler::EventHandler(SDL2pp::Window &window_ref, Queue<std::shared_ptr<Command>> &command_queue)
    : window(&window_ref), cursor(window->GetWidth(), window->GetHeight(), 1000, 1000), command_queue(command_queue) {}

bool EventHandler::handleEvents() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::MOVE_LEFT_INIT));
                        break;
                    case SDLK_RIGHT:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::MOVE_RIGHT_INIT));
                        break;
                    case SDLK_RETURN:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::JUMP_FORWARD));
                        break;
                    case SDLK_BACKSPACE:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::JUMP_BACKWARDS));
                        break;
                    case SDLK_UP:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::AIM_UP_INIT));
                        break;
                    case SDLK_DOWN:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::AIM_DOWN_INIT));
                        break;
                    case SDLK_SPACE:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::WEAPON_PRIMARY_ACTION));
                        break;
                    case SDLK_q:
                        this->command_queue.push(std::make_shared<ChangeWeaponCommand>(WeaponTypeDto::BAZOOKA));
                        break;
                    case SDLK_w:
                        this->command_queue.push(std::make_shared<ChangeWeaponCommand>(WeaponTypeDto::MORTAR));
                        break;
                    case SDLK_e:
                        this->command_queue.push(std::make_shared<ChangeWeaponCommand>(WeaponTypeDto::GREEN_GRENADE));
                        break;
                    case SDLK_r:
                        this->command_queue.push(std::make_shared<ChangeWeaponCommand>(WeaponTypeDto::HOLY_GRENADE));
                        break;
                    case SDLK_f:
                        this->command_queue.push(std::make_shared<ChangeWeaponCommand>(WeaponTypeDto::DYNAMITE));
                        break;
                    case SDLK_1:
                        this->command_queue.push(std::make_shared<ChangeProjectileCountDownCommand>(ProjectileCountDown::ONE));
                        break;
                    case SDLK_2:
                        this->command_queue.push(std::make_shared<ChangeProjectileCountDownCommand>(ProjectileCountDown::TWO));
                        break;
                    case SDLK_3:
                        this->command_queue.push(std::make_shared<ChangeProjectileCountDownCommand>(ProjectileCountDown::THREE));
                        break;
                    case SDLK_4:
                        this->command_queue.push(std::make_shared<ChangeProjectileCountDownCommand>(ProjectileCountDown::FOUR));
                        break;
                    case SDLK_5:
                        this->command_queue.push(std::make_shared<ChangeProjectileCountDownCommand>(ProjectileCountDown::FIVE));
                        break;
                    case SDLK_z:
                        this->command_queue.push(std::make_shared<ToggleCheatCommand>(CheatType::HEALTH));
                        break;
                    case SDLK_x:
                        std::cout << "Sendin cheat\n";
                        this->command_queue.push(std::make_shared<ToggleCheatCommand>(CheatType::MOVEMENT));
                        break;
                    case SDLK_c:
                        this->command_queue.push(std::make_shared<ToggleCheatCommand>(CheatType::WEAPON));
                        break;
                }
            }
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent &keyEvent = (SDL_KeyboardEvent &) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::MOVE_LEFT_END));
                        break;
                    case SDLK_RIGHT:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::MOVE_RIGHT_END));
                        break;
                    case SDLK_UP:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::AIM_UP_STOPPED));
                        break;
                    case SDLK_DOWN:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::AIM_DOWN_STOPPED));
                        break;
                    case SDLK_SPACE:
                        this->command_queue.push(std::make_shared<GameActionCommand>(GameAction::WEAPON_SECONDARY_ACTION));
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

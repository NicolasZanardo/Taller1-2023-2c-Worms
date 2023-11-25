#include "GameNetMessageBehaviour.h"

GameNetMessageBehaviour::GameNetMessageBehaviour(InGameClients &gameClients, GameInstance &game) :
        gameClients(gameClients),
        game(game) {}

void GameNetMessageBehaviour::run(NetMessageChat *msg) {
    std::shared_ptr<NetMessage> message(new NetMessageChat(
        msg->client_id, msg->chat
    ));
    gameClients.sendAll(message);
}

void GameNetMessageBehaviour::run(NetMessageLeave *msg) {
    gameClients.remove(msg->client_id);
    std::cout << "Kicking client " << msg->client_id << "\n";
}

void GameNetMessageBehaviour::run(NetMessageInformID *msg) {
    std::cerr << "The client " << msg->client_id << " informed their id...";
}

void GameNetMessageBehaviour::run(NetMessage_test *msg) {
    std::cerr << "A test message was recieved...";
}

void GameNetMessageBehaviour::run(NetMessageInitialGameState *msg) {
    std::cerr << "Shouldnt receive MessageInitialState...";
}

void GameNetMessageBehaviour::run(NetMessageGameStateUpdate *msg) {
    std::cerr << "Shouldnt receive MessageGameUpdate...";
}

void GameNetMessageBehaviour::run(NetMessageGameAction *msg) {

    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    switch (msg->action) {

        case GameAction::MOVE_RIGHT_INIT: {
            game.start_moving_current_worm_right();
            break;
        }
        case GameAction::MOVE_LEFT_INIT: {
            game.start_moving_current_worm_left();
            break;
        }
        case GameAction::MOVE_RIGHT_END: {
            game.stop_moving_current_worm(); // TODO
            break;
        }
        case GameAction::MOVE_LEFT_END: {
            game.stop_moving_current_worm(); // TODO better mechanics
            break;
        }
        case GameAction::JUMP_BACKWARDS: {
            game.jump_back_current_worm();
            break;
        }
        case GameAction::JUMP_FORWARD: {
            game.jump_forward_current_worm();
            break;
        }
        case GameAction::AIM_UP_INIT: {
            game.start_aiming_up_current_worm();
            break;
        }
        case GameAction::AIM_DOWN_INIT: {
            game.start_aiming_down_current_worm();
            break;
        }
        case GameAction::AIM_UP_STOPPED: {
            game.stop_aiming_up_current_worm();
            break;
        }
        case GameAction::AIM_DOWN_STOPPED: {
            game.stop_aiming_down_current_worm();
            break;
        }
        case GameAction::SHOOT_STARTED: {
            game.start_shot_for_current_worm();
            break;
        }
        case GameAction::SHOOT_ENDED: {
            game.end_shot_for_current_worm();
            break;
        }
    }
}


void GameNetMessageBehaviour::run(NetMessagePlayerChangedWeapon *msg) {
    std::cout << "NetMessageBehaviour received the change weapon call\n";
    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    game.change_weapon_for_current_worm(msg->chosen_weapon);
}
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

    if (!game.isClientsTurn(msg->client_id)) {
        return;
    }
    switch (msg->action) {

        case ActionTypeDto::moving_right_init: {
            game.startMovingCurrentWormRight();
            break;
        }
        case ActionTypeDto::moving_left_init: {
            game.startMovingCurrentWormLeft();
            break;
        }
        case ActionTypeDto::stop_moving: {
            game.stopMovingCurrentWorm();
            break;
        }
        case ActionTypeDto::jump_back: {
            game.jumpBackCurrentWorm();
            break;
        }
        case ActionTypeDto::jump_forward: {
            game.jumpForwardCurrentWorm();
            break;
        }
        case ActionTypeDto::aim_up_init: {
            game.start_aiming_up_current_worm();
            break;
        }
        case ActionTypeDto::aim_down_init: {
            game.start_aiming_down_current_worm();
            break;
        }
        case ActionTypeDto::aim_up_stopped: {
            game.stop_aiming_up_current_worm();
            break;
        }
        case ActionTypeDto::aim_down_stopped: {
            game.stop_aiming_down_current_worm();
            break;
        }
    }
}

void GameNetMessageBehaviour::run(NetMessagePlayerShot *msg) {

    if (!game.isClientsTurn(msg->client_id)) {
        return;
    }
    switch (msg->weapon) {

    }
}
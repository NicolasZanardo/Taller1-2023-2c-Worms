#include "GameNetMessageBehaviour.h"

GameNetMessageBehaviour::GameNetMessageBehaviour(InGameClients &gameClients, GameInstance &game) :
        gameClients(gameClients),
        game(game) {}


void GameNetMessageBehaviour::run(NetMessageChat *msg) {
    gameClients.sendAll(msg);
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
    // TODO separate in different messages?
    switch (msg->action) {
        case ActionTypeDto::moving_left_init: {
            game.startMovingCurrentWormLeft();
        }
        case ActionTypeDto::moving_right_init: {
            game.startMovingCurrentWormRight();
        }
        case ActionTypeDto::stop_moving: {
            game.stopMovingCurrentWorm();
        }
        case ActionTypeDto::jump_back: {
            game.jumpBackCurrentWorm();
        }
        case ActionTypeDto::jump_forward: {
            game.jumpForwardCurrentWorm();
        }
    }
}
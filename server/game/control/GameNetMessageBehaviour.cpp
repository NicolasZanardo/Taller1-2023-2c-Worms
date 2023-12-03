#include "GameNetMessageBehaviour.h"

GameNetMessageBehaviour::GameNetMessageBehaviour(InGameClients &gameClients, GameInstance &game) :
        gameClients(gameClients),
        game(game) {}

void GameNetMessageBehaviour::run(NetMessageChat *msg) {
    std::shared_ptr<NetMessage> message(new NetMessageChat(
        msg->client_id, msg->chat
    ));
    gameClients.send_all(message);
}

void GameNetMessageBehaviour::run(NetMessageGameAction *msg) {
    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    game.input_action_to_current_worm(msg->action);
}

void GameNetMessageBehaviour::run(NetMessagePlayerChangedWeapon *msg) {
    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    game.change_weapon_for_current_worm(msg->chosen_weapon);
}

void GameNetMessageBehaviour::run(NetMessagePlayerChangedProjectileCountdown *msg) {
    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    game.change_projectile_count_down_for_current_worm(msg->count_down);
}

void GameNetMessageBehaviour::run(NetMessagePlayerToggleCheat *msg) {
    if (!game.is_client_turn(msg->client_id)) {
        return;
    }
    game.toggle_cheat_mode_for_current_worm(msg->cheat);
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

void GameNetMessageBehaviour::run(NetMessageGameEnded *msg) {
    std::cerr << "Shouldnt receive MessageGameUpdate...";
}

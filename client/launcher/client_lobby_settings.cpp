#include "client_lobby_settings.h"


ClientLobbySettings::ClientLobbySettings()
    : ready_to_start(false) {}

void ClientLobbySettings::run(NetMessageInformID* msg) {
    this->id = msg->client_id;
}


void ClientLobbySettings::run(NetMessageCreateGameResponse* msg) {
    if (msg->was_created) {
        std::cout << "Game Room was created.\n";
    } else {
        std::cout << "Game Room was not created.\n";
    }
}

void ClientLobbySettings::run(NetMessageJoinGameResponse* msg) {
    if (msg->was_joined) {
        std::cout << "Game Room was joined.\n";
    } else {
        std::cout << "Game Room was not joined.\n";
    }
}

void ClientLobbySettings::run(NetMessageListGamesResponse* msg) {
    this->games_info = std::move(msg->games_info);
}

void ClientLobbySettings::run(NetMessageStartGame* msg) {
    std::cout << "client starting game\n";
    this->ready_to_start = true;
}

void ClientLobbySettings::run(NetMessageInitialGameState* msg) {
    game_state_dto = std::make_shared<ClientGameStateDTO>();

    game_state_dto->width = msg->room_width;
    game_state_dto->height = msg->room_height;
    game_state_dto->water_level_height = msg->water_height_level;
    game_state_dto->beams = std::move(msg->beams);
    game_state_dto->worms = std::move(msg->worms);
    game_state_dto->client_ids_turn_order = std::move(msg->client_ids_turn_order);
}

#include "client_lobby_settings.h"


ClientLobbySettings::ClientLobbySettings()
    : ready_to_start(false) {}

void ClientLobbySettings::run(NetMessageInformID* msg) {
    std::cout << "Received my id, im client: " << msg->client_id <<"\n";
    this->id = msg->client_id;
}


void ClientLobbySettings::run(NetMessageCreateGameResponse* msg) {
    std::cout << "Response of create game was.\n";
    if (msg->was_created) {
        std::cout << "Game Room was created.\n";
    } else {
        std::cout << "Game Room was not created.\n";
    }
}

void ClientLobbySettings::run(NetMessageJoinGameResponse* msg) {
    std::cout << "Response of join game was.\n";
    if (msg->was_joined) {
        std::cout << "Game Room was joined.\n";
    } else {
        std::cout << "Game Room was not joined.\n";
    }
}

void ClientLobbySettings::run(NetMessageListGamesResponse* msg) {
    std::cout << "Response of list games was.\n";
    for (auto& game_info : msg->games_info) {
        std::cout << "Room: " << game_info.name
                << " - Scenario: " << game_info.scenario
                << " - Players (" << static_cast<uint16_t>(game_info.joined_players)
                << '/' << static_cast<uint16_t>(game_info.total_players) << '\n';
    }
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

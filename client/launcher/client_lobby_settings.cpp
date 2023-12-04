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
                << " - Players (" << game_info.joined_players
                << '/' << game_info.total_players << '\n';
    }
}

void ClientLobbySettings::run(NetMessageStartGame* msg) {
    this->ready_to_start = true;
}

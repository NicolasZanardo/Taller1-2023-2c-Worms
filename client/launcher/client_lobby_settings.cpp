#include "client_lobby_settings.h"

ClientLobbySettings::ClientLobbySettings()
    : ready_to_start(false) {}

void ClientLobbySettings::run(NetMessageCreateGameResponse* msg) {
    if (msg->was_created) {
        std::cout << "Game Room was created.\n";
    }

    std::cout << "Game Room was not created.\n";
}

void ClientLobbySettings::run(NetMessageJoinGameResponse* msg) {
    if (msg->was_joined) {
        std::cout << "Game Room was created.\n";
    }

    std::cout << "Game Room was not created.\n";
}

void ClientLobbySettings::run(NetMessageListGamesResponse* msg) {
    for (auto& game_info : msg->games_info) {
        std::cout << "Room: " << game_info.game_room
                << " - Scenario: " << game_info.scenario
                << " - Players (" << game_info.joined_players
                << '/' << game_info.total_players << '\n';
    }
}

void ClientLobbySettings::run(NetMessageStartGame* msg) {
    this->ready_to_start = true;
}

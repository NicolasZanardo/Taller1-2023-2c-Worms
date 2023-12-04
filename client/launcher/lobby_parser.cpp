#include "lobby_parser.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "networking.h"

#define CLIENT_COMMAND_CREATE "create"
#define CLIENT_COMMAND_JOIN "join"
#define CLIENT_COMMAND_LIST "list"

std::unique_ptr<NetMessage> LobbyParser::parse(const std::string& str) {
    std::string action;
    std::istringstream iss(str);

    iss >> action >> std::ws;
    if (action == CLIENT_COMMAND_CREATE) {
        std::string game_room;
        std::string scenario;
        uint16_t num_players;

        // Los nombres de la sala y el escenario no deben tener espacios.
        iss >> game_room >> scenario >> num_players;
        std::cout << "Request to create a game sended\n";

        return std::make_unique<NetMessageCreateGame>(game_room, scenario, num_players);
    } else if (action == CLIENT_COMMAND_JOIN) {
        std::string game_room;

        std::getline(iss, game_room);
        std::cout << "Request to join a game sended\n";

        return std::make_unique<NetMessageJoinGame>(game_room);
    } else if (action == CLIENT_COMMAND_LIST) {
        std::cout << "Request to list all games sended\n";
        return std::make_unique<NetMessageListGames>();
    } else {
        std::runtime_error("Error: parse invalid action.\n");
    }

    return nullptr;
}
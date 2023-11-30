#include "lobby_parser.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

#include "networking.h"

#define CLIENT_COMMAND_CREATE "create"
#define CLIENT_COMMAND_JOIN "join"
#define CLIENT_COMMAND_LIST "list"

std::unique_ptr<ClientAction> Parser::parse(const std::string& str) {
    std::string action;
    std::istringstream iss(str);

    iss >> action >> std::ws;
    if (action == CLIENT_COMMAND_CREATE) {
        std::string game_room;
        std::string scenario;
        uint16_t num_players;

        // Los nombres de la sala y el escenario no deben tener espacios.
        iss >> game_room >> scenario >> num_players;

        return std::make_unique<NetMessageCreateGame>(std::move(game_room),
                        std::move(scenario), static_cast<uint8_t>(num_players));
    } else if (action == CLIENT_COMMAND_JOIN) {
        std::string game_room;

        std::getline(iss, game_room);

        return std::make_unique<NetMessageJoinGame>(std::move(game_room));
    } else if (action == CLIENT_COMMAND_LIST) {
        return std::make_unique<NetMessageListGames>();
    } else {
        std::runtime_error("Error: parse invalid action.\n");
    }

    return nullptr;
}
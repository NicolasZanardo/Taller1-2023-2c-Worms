#include "client_console_parser.h"

#include <stdexcept>

#include "client_request.h"

#define CLIENT_COMMAND_CREATE_GAME "Create"
#define CLIENT_COMMAND_JOIN_GAME "Join"
#define CLIENT_COMMAND_LEAVE_GAME "Leave"

Parser::Parser():
        parse_map{{std::string(CLIENT_COMMAND_CREATE_GAME), &Parser::parseRequestCreateGame},
                  {std::string(CLIENT_COMMAND_JOIN_GAME), &Parser::parseRequestJoinGame},
                  {std::string(CLIENT_COMMAND_LEAVE_GAME), &Parser::parseRequestLeaveGame}} {}

std::unique_ptr<ClientAction> Parser::parse(const std::string& str) {
    std::string action;
    std::istringstream iss(str);

    iss >> action >> std::ws;

    if (this->parse_map.find(action) != this->parse_map.end()) {
        return std::move((this->*(this->parse_map[action]))(iss));
    }

    throw std::runtime_error("Error: Parse Invalid Action.\n");
}

std::unique_ptr<ClientAction> Parser::parseRequestCreateGame(std::istringstream& iss) {
    std::string room_name;
    std::getline(iss, room_name);

    uint16_t num_worms;
    iss >> num_worms;

    return std::make_unique<ClientRequestCreateGame>(std::move(room_name));
}

std::unique_ptr<ClientAction> Parser::parseRequestJoinGame(std::istringstream& iss) {
    std::string room_name;

    std::getline(iss, room_name);

    return std::make_unique<ClientRequestJoinGame>(std::move(room_name));
}

std::unique_ptr<ClientAction> Parser::parseRequestLeaveGame(std::istringstream& iss) {
    return std::make_unique<ClientRequestLeaveGame>();
}
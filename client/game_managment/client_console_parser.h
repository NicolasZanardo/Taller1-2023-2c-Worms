#ifndef __CLIENT_CONSOLE_PARSER_H__
#define __CLIENT_CONSOLE_PARSER_H__

#include "client_request.h"

class ClientConsoleParser {
public:
    ClientConsoleParser();
    ~ClientConsoleParser() = default;

    ClientConsoleParser(const ClientConsoleParser& other) = delete;
    ClientConsoleParser& operator=(const Parser& other) = delete;

    ClientConsoleParser(ClientConsoleParser&& other) = delete;
    ClientConsoleParser& operator=(ClientConsoleParser&& other) = delete;

    std::unique_ptr<ClientRequest> parse(const std::string& str);

    std::unique_ptr<ClientRequest> parseRequestCreateGame(std::istringstream& iss);
    std::unique_ptr<ClientRequest> parseRequestJoinGame(std::istringstream& iss);
    std::unique_ptr<ClientRequest> parseRequestLeaveGame(std::istringstream& iss);

private:
    std::map<std::string, std::unique_ptr<ClientRequest> (ClientConsoleParser::*)(std::istringstream&)> parse_map;
};


#endif  // __CLIENT_CONSOLE_PARSER_H__

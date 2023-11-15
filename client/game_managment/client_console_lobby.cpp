#include "client_console_lobby_h"

#include <iostream>

void ClientConsoleLobby::execute() {
    while (!std::cin.eof()) {
    std::string input_string;

    std::getline(std::cin, input_string);
    if (input_string.empty()) {
        continue;
    }

    // std::unique_ptr<ClientRequest> request = this->parser.parse(input_string);
    // request->execute(this->client_protocol);

    // if ready to play break
}
}

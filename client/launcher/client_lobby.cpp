#include "./client_lobby.h"

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#include "networking.h"

ClientLobby::ClientLobby(const char *host_name, const char *service_name)
    : net_channel(host_name, service_name) {}

void ClientLobby::execute() {
    while (!input_stream.eof()) {
        std::string input_string;

        std::getline(std::cin, input_string);
        if (input_string.empty()) {
            continue;
        }

        std::unique_ptr<NetMessage> request = this->parser.parse(input_string);

        if (!(this->net_channel.is_open())) {
            break;
        }

        this->net_channel.send_message(*request);

        std::unique_ptr<NetMessage> response(this->net_channel.read_message());
        response->execute(this->lobby_settings);

        if (this->lobby_settings.isReadyToStart()) {
            std::cout << "Starting game.\n";
            break;
        }
    }
}
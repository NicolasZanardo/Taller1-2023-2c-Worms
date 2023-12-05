#include "./client_lobby.h"

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#include "networking.h"

// ClientLobby::ClientLobby(const char *host_name, const char *service_name, ClientLobbySettings& lobby_settings)
    // : lobby_settings(lobby_settings)
    // , net_channel(host_name, service_name) {}

ClientLobby::ClientLobby(NetChannel& net_channel, ClientLobbySettings& lobby_settings)
    : net_channel(net_channel)
    , lobby_settings(lobby_settings) {}

void ClientLobby::execute() {
    std::unique_ptr<NetMessage> received_id_msg(this->net_channel.read_message());
    received_id_msg->execute(this->lobby_settings);
    
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
        std::cout <<  static_cast<int>(response->msg_type) << std::endl;
        response->execute(this->lobby_settings);

        if (this->lobby_settings.isReadyToStart()) {
            std::cout << "Starting game.\n";
            break;
        }
    }
}
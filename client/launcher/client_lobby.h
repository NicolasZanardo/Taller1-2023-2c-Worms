#ifndef __CLIENT_LOBBY_H__
#define __CLIENT_LOBBY_H__

#include <fstream>

#include "client_lobby_settings.h"
#include "lobby_parser.h"
#include "queue.h"
#include "networking.h"
#include "../game_ui/utils_constants.h"

class ClientLobby {
public:
    ClientLobby() = delete;
    // explicit ClientLobby(const char* host_name, const char* service_name, ClientLobbySettings& lobby_settings);
    explicit ClientLobby(NetChannel& net_channel, ClientLobbySettings& lobby_settings);
    ~ClientLobby() = default;

    ClientLobby(const ClientLobby& other) = delete;
    ClientLobby& operator=(const ClientLobby& other) = delete;

    ClientLobby(ClientLobby&& other) = delete;
    ClientLobby& operator=(ClientLobby&& other) = delete;

    void execute();

private:
    std::ifstream input_stream;
    LobbyParser parser;
    NetChannel& net_channel;
    ClientLobbySettings& lobby_settings;
};

#endif  // __CLIENT_LOBBY_H__
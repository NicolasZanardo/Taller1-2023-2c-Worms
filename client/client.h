#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>
#include <memory>

#include "queue.h"
#include "networking.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "client_game_state_dto.h"
#include "game_display.h"
#include "game_ui/utils_constants.h"
#include "launcher/client_lobby_settings.h"

class Client {
public:
    Client() = delete;
    // explicit Client(const char* host_name, const char* service_name);
    explicit Client(NetChannel& net_channel, ClientLobbySettings& lobby_settings);
    ~Client() = default;

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;

    void execute();

private:
    Queue<std::shared_ptr<Command>> command_queue;
    Queue<std::shared_ptr<ClientGameStateDTO>> state_queue;

    NetChannel& channel;
    ClientLobbySettings& lobby_settings;
    GameDisplay display;
    ClientReceiver receiver;
    ClientSender sender;
};

#endif  // __CLIENT_H__

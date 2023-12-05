#ifndef TP_WORMS_CLIENT_H_
#define TP_WORMS_CLIENT_H_

#include <unistd.h>
#include <memory>
#include <unistd.h>
#include "queue.h"
#include "Command.h"
#include "networking.h"
#include "launcher/client_lobby_settings.h"
#include "game_display/game_display.h"
#include "client_receiver.h"
#include "client_sender.h"

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

#endif

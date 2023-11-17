#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <unistd.h>

#include <memory>

#include "queue.h"

#include <SDL2pp/SDL2pp.hh>

#include "networking.h"
#include "client_receiver.h"
#include "client_sender.h"
#include "game_loop.h"
#include "client_game_state_dto.h"

class Client {
public:
    Client() = delete;
    explicit Client(const char* host_name, const char* service_name);
    ~Client() = default;

    Client(const Client& other) = delete;
    Client& operator=(const Client& other) = delete;

    Client(Client&& other) = delete;
    Client& operator=(Client&& other) = delete;

    void execute();

private:
    Queue<GameEvent> echo_queue;  // temp.

    Queue<GameEvent> event_queue;
    Queue<std::shared_ptr<ClientGameStateDTO>> state_queue;

    NetChannel channel;

    ClientReceiver receiver;
    ClientSender sender;
};

#endif  // __CLIENT_H__

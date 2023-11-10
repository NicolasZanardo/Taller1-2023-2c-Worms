#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <unistd.h>

#include <SDL2pp/SDL2pp.hh>

#include "client_receiver.h"
#include "client_sender.h"
#include "game_loop.h"

#include "queue.h"

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
    Queue<GameEvent> event_queue;
    Queue<GameEvent> state_queue;
    Queue<GameEvent> echo_queue;  // temp.

    ClientReceiver receiver;
    ClientSender sender;
};

#endif  // __CLIENT_H__

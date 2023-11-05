#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <unistd.h>

#include <SDL2pp/SDL2pp.hh>

#include "client_receiver.h"
#include "client_sender.h"
#include "event_handler.h"

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
    void render(SDL2pp::Renderer &renderer, Player &player);
    void update(Player &player, float dt);

    Queue<GameEvent> event_queue;
    Queue<GameEvent> state_queue;
    Queue<GameEvent> echo_queue;  // temp.

    ClientReceiver receiver;
    ClientSender sender;
    
    EventHandler event_handler;
};

#endif  // __CLIENT_H__
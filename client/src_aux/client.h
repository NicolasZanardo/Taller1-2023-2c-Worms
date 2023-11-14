#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>
#include "presentation/EventHandler.h"
#include "model/Worm.h"

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
    EventHandler eventHandler;
    bool handleEvents(Worm &worm);
};

#endif  // __CLIENT_H__

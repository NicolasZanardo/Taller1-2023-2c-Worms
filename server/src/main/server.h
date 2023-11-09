#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <vector>
#include <memory>
#include "../lobby/waiting_lobby.h"
#include "../lobby/client_accepter.h"

class Server {
    WaitingLobby lobby;
    ClientAccepter accepter;
public:
    explicit Server(const char* servname);
    ~Server();
    void execute();

    void handle_input();
    void kick(std::vector<std::string>&);
    void chat(std::vector<std::string>&);
    void error(std::vector<std::string>&, std::string&);

private:
    Server() = delete;
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;
};

#endif  // __SERVER_H__

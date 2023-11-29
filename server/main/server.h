#ifndef __SERVER_H__
#define __SERVER_H__

#include <list>
#include <mutex>
#include <string>
#include <vector>
#include <memory>
#include "waiting_lobby.h"
#include "client_accepter.h"

class Server {
    WaitingLobby lobby;
    ClientAccepter accepter;

    std::mutex active_games_mtx;
    std::list<GameEngineInstance*> active_games;
    
public:
    explicit Server(const char* servname);
    ~Server();
    void execute();

    void handle_input();
    void kick(std::vector<std::string>&);
    void chat(std::vector<std::string>&);
    void start(std::vector<std::string>&);
    void send_test_message(std::vector<std::string>&);
    void error(std::vector<std::string>&, std::string&);

private:
    Server() = delete;
    Server(const Server& other) = delete;
    Server& operator=(const Server& other) = delete;
    Server(Server&& other) = delete;
    Server& operator=(Server&& other) = delete;
};

#endif  // __SERVER_H__

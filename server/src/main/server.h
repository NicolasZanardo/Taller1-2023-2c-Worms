#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <vector>
#include "../lobby/waiting_lobby.h"

class Server {
    const char* servname;
	WaitingLobby* lobby;
public:
    explicit Server(const char* servname);
    ~Server();
    void execute();
    void test_isHost(bool isHost);

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

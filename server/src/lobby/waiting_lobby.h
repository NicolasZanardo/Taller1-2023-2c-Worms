#ifndef SERVER_WAITING_LOBBY_H_
#define SERVER_WAITING_LOBBY_H_

#include <list>
#include <mutex>
#include <string>
#include "../client/client.h"
#include "../../../common_base/thread.h"
#include "../../../common_base/networking.h"

class WaitingLobby : public Thread {
    Socket host;
    std::mutex clients_mtx;
    std::list<Client*> clients;
    void remove_zombies();

    public:
    explicit WaitingLobby(const char* servname);

    void run() override;
    void stop() override;
    void kick(const int client_id);
    void chat(const int client_id, std::string& msg);
};
#endif

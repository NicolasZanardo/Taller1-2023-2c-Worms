#ifndef SERVER_WAITING_LOBBY_H_
#define SERVER_WAITING_LOBBY_H_

#include <list>
#include <mutex>
#include <string>
#include "../GameInstance.h"
#include "../client/client.h"
#include "../../../common_base/thread.h"
#include "../../../common_base/networking.h"
#include "../../../common_base/Networking/dtos/HardcodedScenarioData.h"

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
    void start_game(); // TODO For now 1 Game
};
#endif


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

class WaitingLobby : public Thread, public NetMessageBehaviour {
    std::mutex clients_mtx;
    std::list<Client*> clients;
    NetQueue input_queue;
    void remove_zombies();

    public:
    explicit WaitingLobby();

    void run() override;
    void stop() override;
    void start_game(); // TODO For now 1 Game
    void add(Client* new_client);


    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
};
#endif


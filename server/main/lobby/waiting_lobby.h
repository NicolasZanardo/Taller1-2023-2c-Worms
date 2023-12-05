#ifndef SERVER_WAITING_LOBBY_H_
#define SERVER_WAITING_LOBBY_H_

#include <list>
#include <mutex>
#include <string>
#include "GameEngineInstance.h"
#include "server_client.h"
#include "thread.h"
#include "networking.h"

class Client;
class GameEngineInstance;
#include "HardcodedScenarioData.h"

class WaitingLobby { // : public Thread, public NetMessageBehaviour {
    std::mutex mtx;
    // std::list<Client*> clients;
    std::list<std::unique_ptr<Client>> clients;
    NetQueue input_queue;

public:
    explicit WaitingLobby();
    ~WaitingLobby() = default;

    // void run() override;
    // void stop() override;
    // void add(Client* new_client);
    void addClient(const int id, Socket skt, GamesManager& games_manager);
    void removeZombies();
    void removeAll();

    // GameEngineInstance* start_game();

    // void run(NetMessageChat* msg) override;
    // void run(NetMessageLeave* msg) override;
    // void run(NetMessage_test* msg) override;
    // void run(NetMessageInformID* msg) override;
    // void run(NetMessageInitialGameState* msg) override;
    // void run(NetMessageGameStateUpdate* msg) override;
    // void run(NetMessageGameAction* msg) override;
    // void run(NetMessagePlayerChangedWeapon* msg) override;
    // void run(NetMessagePlayerChangedProjectileCountdown* msg) override;
    // void run(NetMessageGameEnded* msg) override;

    // void run(NetMessageCreateGame* msg) override { }
    // void run(NetMessageListGames* msg) override { }
    // void run(NetMessageJoinGame* msg) override { }

    // void run(NetMessageCreateGameResponse* msg) override { }
    // void run(NetMessageJoinGameResponse* msg) override { }
    // void run(NetMessageListGamesResponse* msg) override { }

    // void run(NetMessageStartGame* msg) override { }
};

#endif  // SERVER_WAITING_LOBBY_H_

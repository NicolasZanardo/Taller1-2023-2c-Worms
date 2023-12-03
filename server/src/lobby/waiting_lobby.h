#ifndef SERVER_WAITING_LOBBY_H_
#define SERVER_WAITING_LOBBY_H_

#include <list>
#include <mutex>
#include <string>
#include "../game/control/GameEngineInstance.h"
#include "../client/client.h"
#include "../../../common_base/thread.h"
#include "../../../common_base/networking.h"

class Client;
class GameEngineInstance;
#include "../game/scenario/HardcodedScenarioData.h"

class WaitingLobby : public Thread, public NetMessageBehaviour {
    std::mutex clients_mtx;
    std::list<Client*> clients;  // NOTA: Usar contenedores con referencias seguras.
    NetQueue input_queue;

    void remove_zombies();

    public:
    explicit WaitingLobby();

    void run() override;
    void stop() override;
    void add(Client* new_client);
    GameEngineInstance* start_game(); // TODO For now 1 Game


    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
    void run(NetMessageGameAction* msg) override;
    void run(NetMessagePlayerChangedWeapon* msg) override;
    void run(NetMessagePlayerChangedProjectileCountdown* msg) override;

    void run(NetMessageCreateGame* msg) override { }
    void run(NetMessageListGames* msg) override { }
    void run(NetMessageJoinGame* msg) override { }

    void run(NetMessageCreateGameResponse* msg) override { }
    void run(NetMessageJoinGameResponse* msg) override { }
    void run(NetMessageListGamesResponse* msg) override { }

    void run(NetMessageStartGame* msg) override { }
};
#endif


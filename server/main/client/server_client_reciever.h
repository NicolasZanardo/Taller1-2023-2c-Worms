#ifndef SERVER_CLIENT_RECIEVER_H_
#define SERVER_CLIENT_RECIEVER_H_

#include <memory>

#include "thread.h"
#include "networking.h"

#include "../lobby/games_manager.h"
// TODO ARREGLAR EL INCLUDE
class Client;

class Reciever : public Thread, public NetMessageBehaviour {
    const int client_id;
    Client* client;
    NetChannel* channel;
    NetQueue* game_queue;
    NetQueue* send_queue;
    GamesManager* games_manager;

    std::string game_room;
    std::shared_ptr<NetMessage> msg;

    public:
    Reciever(const int client_id, Client& client, NetChannel* channel, NetQueue& send_queue, GamesManager& games_manager);
    
    void run() override;
    void stop() override;
    void switch_lobby(NetQueue* game_queue);
    
    ~Reciever();

    void run(NetMessageChat* msg) override;
    void run(NetMessageLeave* msg) override;
    void run(NetMessage_test* msg) override;
    void run(NetMessageInformID* msg) override;
    void run(NetMessageInitialGameState* msg) override;
    void run(NetMessageGameStateUpdate* msg) override;
    void run(NetMessageGameAction* msg) override;
    void run(NetMessagePlayerChangedWeapon* msg) override;
    void run(NetMessagePlayerChangedProjectileCountdown* msg) override;
    void run(NetMessagePlayerToggleCheat* msg) override;
    void run(NetMessageGameEnded* msg) override;

    void run(NetMessageCreateGame* msg) override;
    void run(NetMessageListGames* msg) override;
    void run(NetMessageJoinGame* msg) override;

    void run(NetMessageCreateGameResponse* msg) override { }
    void run(NetMessageJoinGameResponse* msg) override { }
    void run(NetMessageListGamesResponse* msg) override { }

    void run(NetMessageStartGame* msg) override;
};
#endif 

#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include "../../../common_base/networking.h"
#include "client_reciever.h"
#include "client_sender.h"

#include "../lobby/games_manager.h"

class Client {
    NetChannel channel;
    NetQueue  send_queue;
    NetQueue* game_queue;
    Reciever msg_reciever;
    Sender msg_sender;
    GamesManager* games_manager;

    public:
    const int id;
    Client(const int id, Socket skt, GamesManager& games_manager);

    const bool is_alive() const;
    int getID() const;
    void switch_lobby(NetQueue* game_queue);
    void communicate(std::shared_ptr<NetMessage> net_message);
    void disconnect();

    ~Client();
};
#endif 

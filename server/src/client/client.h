#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include "../../../common_base/networking.h"
#include "client_reciever.h"
#include "client_sender.h"

class Client {
    NetChannel channel;
    NetQueue  send_queue;
    NetQueue* game_queue;
    Reciever msg_reciever;
    Sender msg_sender;

    public:
    const int id;
    Client(const int id, Socket skt);

    const bool is_alive() const;
    void switch_lobby(NetQueue* game_queue);
    void communicate(NetMessage* net_message);
    void disconnect();

    ~Client();
};
#endif 

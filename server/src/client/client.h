#ifndef SERVER_CLIENT_H_
#define SERVER_CLIENT_H_

#include "../../../common_base/networking.h"
#include "../../../common_base/queue.h"
#include "client_reciever.h"
#include "client_sender.h"

class Client {
    NetChannel channel;
    Queue<NetMessage*>  send_queue;
    Queue<NetMessage*>* game_queue;
    Reciever msg_reciever;
    Sender msg_sender;

    public:
    const int id;
    Client(const int id, Socket skt);

    const bool is_alive() const;
    void switch_lobby(Queue<NetMessage*>* game_queue);
    void communicate(NetMessage* net_message);
    
    ~Client();
};
#endif 

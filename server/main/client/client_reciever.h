#ifndef SERVER_CLIENT_RECIEVER_H_
#define SERVER_CLIENT_RECIEVER_H_

#include "thread.h"
#include "networking.h"

class Reciever : public Thread {
    const int client_id;
    NetChannel* channel;
    NetQueue* game_queue;

    public:
    Reciever(const int client_id, NetChannel* channel);
    
    void run() override;
    void stop() override;
    void switch_lobby(NetQueue* game_queue);
    
    ~Reciever();
};
#endif 

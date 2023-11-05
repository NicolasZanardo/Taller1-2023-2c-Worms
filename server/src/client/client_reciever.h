#ifndef SERVER_CLIENT_RECIEVER_H_
#define SERVER_CLIENT_RECIEVER_H_

#include "../../../common_base/queue.h"
#include "../../../common_base/thread.h"
#include "../../../common_base/networking.h"

class Reciever : public Thread {
    const int client_id;
    NetChannel* channel;
    Queue<NetMessage*>* game_queue;

    public:
    Reciever(const int client_id);
    
    void run() override;
    void stop() override;
    void set_channel(NetChannel* channel);
    void switch_lobby(Queue<NetMessage*>* game_queue);
    
    ~Reciever();
};
#endif 

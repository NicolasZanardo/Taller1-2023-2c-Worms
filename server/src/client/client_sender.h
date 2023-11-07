#ifndef SERVER_CLIENT_SENDER_H_
#define SERVER_CLIENT_SENDER_H_

#include "../../../common_base/queue.h"
#include "../../../common_base/thread.h"
#include "../../../common_base/networking.h"

class Sender : public Thread {
    const int client_id;
    NetChannel* channel;
    NetQueue* client_queue;

    public:
    Sender(const int client_id, NetChannel* channel, NetQueue* client_queue);
    
    void run() override;
    void stop() override;
    
    ~Sender();
};
#endif 

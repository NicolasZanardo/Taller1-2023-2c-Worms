#ifndef COMMON_NET_OPERATOR_H_
#define COMMON_NET_OPERATOR_H_

#include <map>
#include <memory>
#include "../thread.h"
#include "Messages/net_queue.h"
#include "Messages/net_message_behaviour.h"

class NetOperator : public Thread {
    NetQueue queue;
    NetMessageBehaviour* behaviour;

    public:
    NetOperator(NetMessageBehaviour* new_behaviour);
    NetQueue* get_queue();
    virtual void run() override;
    virtual void stop() override;
    ~NetOperator();
};
#endif

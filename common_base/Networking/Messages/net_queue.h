#ifndef COMMON_NET_QUEUE_H_
#define COMMON_NET_QUEUE_H_

#include "../../queue.h"
class NetMessage;

class NetQueue : public Queue<std::shared_ptr<NetMessage>> {
    public:
    explicit NetQueue(const unsigned int size);
};
#endif

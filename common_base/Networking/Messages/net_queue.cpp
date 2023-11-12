#include "net_queue.h"

NetQueue::NetQueue(const unsigned int size) : Queue<std::shared_ptr<NetMessage>>(size) {}

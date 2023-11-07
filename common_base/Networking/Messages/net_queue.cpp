#include "net_queue.h"

NetQueue::NetQueue(const unsigned int size) : Queue<NetMessage*>(size) {}

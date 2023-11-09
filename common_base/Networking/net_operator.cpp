#include "net_operator.h"
#include "Messages/net_message.h"
using namespace std;

NetOperator::NetOperator(NetMessageBehaviour* new_behaviour) :
    Thread(), queue(50),
    behaviour(move(new_behaviour))
    {}

NetOperator::~NetOperator() {
    join();
}

NetQueue* NetOperator::get_queue() {
    return &queue;
}

void NetOperator::stop() {
    queue.close();
}

void NetOperator::run() {
    while (keep_running_) {
        try {
            NetMessage* msg = queue.pop();
            msg->execute(*behaviour);
            delete msg;
        } catch (const ClosedQueue& ex) {
            keep_running_ = false;
        }
    }
}

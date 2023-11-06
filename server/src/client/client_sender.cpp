#include "client_sender.h"

Sender::Sender(const int client_id,  NetChannel* channel, NetQueue* client_queue) : 
    Thread(), 
    client_id(client_id),
    channel(channel),
    client_queue(client_queue)
    {}

void Sender::run() {
    while (keep_running_) {
        try {
            if (client_queue == nullptr) {
                stop();
                return;
            }
            
            NetMessage* msg = client_queue->pop();
            if (client_queue != nullptr && channel != nullptr) {
                channel->send_message(*msg);
            }
            delete msg;

        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void Sender::stop() {
    keep_running_ = false;
    client_queue = nullptr;
}

Sender::~Sender() {
    join();
}
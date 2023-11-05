#include "client_sender.h"

Sender::Sender(const int client_id) : 
    Thread(), client_id(client_id)
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

void Sender::set_channel(NetChannel* new_channel, Queue<NetMessage*>* new_queue) {
    channel = new_channel;
    client_queue = new_queue;
}


Sender::~Sender() {
    join();
}
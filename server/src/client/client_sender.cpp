#include "client_sender.h"

Sender::Sender(const int client_id) : 
    Thread(), client_id(client_id)
    {}

void Sender::run() {
    while (keep_running_) {
        try {
            NetMessage* msg = channel->read_message();

            if (client_queue != nullptr)
                client_queue->push(msg);
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
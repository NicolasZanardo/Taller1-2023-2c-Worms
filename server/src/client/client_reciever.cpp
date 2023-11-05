#include "client_reciever.h"

Reciever::Reciever(const int client_id) : 
    Thread(), client_id(client_id)
    {}

void Reciever::run() {
    while (keep_running_) {
        try {
            NetMessage* msg = channel->read_message();

            if (game_queue != nullptr)
                game_queue->push(msg);
        } catch (const std::exception& ex) {
            keep_running_ = false;
        }
    }
}

void Reciever::stop() {
    keep_running_ = false;
    game_queue = nullptr;
}

void Reciever::switch_lobby(Queue<NetMessage*>* new_game_queue) {
    this->game_queue = new_game_queue;
}

void Reciever::set_channel(NetChannel* new_channel) {
    this->channel = new_channel;
}


Reciever::~Reciever() {
    this->join();
}
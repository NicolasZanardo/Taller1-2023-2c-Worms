#include "client_reciever.h"

Reciever::Reciever(const int client_id, NetChannel* channel) : 
    Thread(), 
    client_id(client_id),
    channel(channel)
    {}

void Reciever::run() {
    while (keep_running_) {
        try {
            std::shared_ptr<NetMessage> msg(channel->read_message());
            if (game_queue != nullptr)
                game_queue->push(msg);
        } catch (const std::exception& ex) {
            keep_running_ = false;
            std::shared_ptr<NetMessage> msg( new NetMessageLeave(client_id));
            game_queue->push(msg);
        }
    }
}

void Reciever::stop() {
    keep_running_ = false;
    game_queue = nullptr;
}

void Reciever::switch_lobby(NetQueue* new_game_queue) {
    game_queue = new_game_queue;
}

Reciever::~Reciever() {
    join();
}
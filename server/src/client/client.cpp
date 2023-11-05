#include "client.h"
#include <iostream>

Client::Client(const int id, Socket skt) :
    channel(std::move(skt)),
    send_queue(60),
    game_queue(nullptr),
    msg_reciever(id),
    id(id)
    {
        msg_reciever.set_channel(&this->channel);
        msg_reciever.start();
    }

const bool Client::is_alive() const {
    return channel.is_open() && msg_reciever.is_alive();
}

Client::~Client() {
    send_queue.close();
    msg_reciever.stop();
    channel.dissconect();
    std::cout << "Dissconecting client " << id << "\n";
}

void Client::switch_lobby(Queue<NetMessage*>* new_game_queue) {
    this->game_queue = new_game_queue;
    this->msg_reciever.switch_lobby(new_game_queue);
}

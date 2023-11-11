#include "client.h"
#include <iostream>

Client::Client(const int id, Socket skt) :
    channel(std::move(skt)),
    send_queue(60),
    game_queue(nullptr),
    msg_reciever(id, &this->channel),
    msg_sender(id, &this->channel, &this->send_queue),
    id(id)
    {
        msg_reciever.start();
        msg_sender.start();
    }

const bool Client::is_alive() const {
    return channel.is_open() && msg_reciever.is_alive() && msg_sender.is_alive();
}

Client::~Client() {
    if (is_alive())
        disconnect();
}

void Client::switch_lobby(NetQueue* new_game_queue) {
    game_queue = new_game_queue;
    msg_reciever.switch_lobby(new_game_queue);
}

void Client::communicate(NetMessage* net_message) {
    try {
        send_queue.push(net_message);
    } catch (std::exception& ex) {
        delete(net_message);
    }
}

void Client::disconnect() {
    msg_sender.stop();
    msg_reciever.stop();

    send_queue.close();
    channel.dissconect();
}

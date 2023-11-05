#include "client.h"
#include <iostream>

Client::Client(const int id, Socket skt) :
    channel(std::move(skt)),
    send_queue(60),
    game_queue(nullptr),
    msg_reciever(id),
    msg_sender(id),
    id(id)
    {
        msg_reciever.set_channel(&channel);
        msg_sender.set_channel(&channel, &send_queue);

        msg_reciever.start();
        msg_sender.start();
    }

const bool Client::is_alive() const {
    return channel.is_open() && msg_reciever.is_alive() && msg_sender.is_alive();
}

Client::~Client() {
    msg_sender.stop();
    msg_reciever.stop();

    send_queue.close();
    channel.dissconect();
    std::cout << "Dissconecting client " << id << "\n";
}

void Client::switch_lobby(Queue<NetMessage*>* new_game_queue) {
    this->game_queue = new_game_queue;
    this->msg_reciever.switch_lobby(new_game_queue);
}

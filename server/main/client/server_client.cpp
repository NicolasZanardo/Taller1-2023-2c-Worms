#include "server_client.h"
#include <iostream>

#include "../lobby/games_manager.h"

Client::Client(const int id, Socket skt, GamesManager& games_manager) :
    games_manager(&games_manager),
    channel(std::move(skt)),
    send_queue(60),
    game_queue(nullptr),
    msg_reciever(id, *this, &this->channel, this->send_queue, *(this->games_manager)),
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

int Client::getID() const {
    return this->id;
}

void Client::switch_lobby(NetQueue* new_game_queue) {
    game_queue = new_game_queue;
    msg_reciever.switch_lobby(new_game_queue);
}

void Client::communicate(std::shared_ptr<NetMessage> net_message) {
    try {
        send_queue.push(net_message);
    } catch (std::exception& ex) {
        /// No le importa
    }
}

void Client::disconnect() {
    msg_sender.stop();
    msg_reciever.stop();

    send_queue.close();
    channel.dissconect();
}

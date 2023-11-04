#include "client.h"
#include <iostream>

Client::Client(const int id, Socket skt) :
    channel(std::move(skt)),
    id(id)
    {}

const bool Client::is_alive() const {
    return channel.is_open();
}

Client::~Client() {
    std::cout << "Dissconecting client " << id << "\n";
}
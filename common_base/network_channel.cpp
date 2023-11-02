#include "network_channel.h"
#include "Networking/connection_lost_exception.h"
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>
#include <utility>

NetworkChannel::NetworkChannel(Socket& skt) : index(0), read_index(0), skt(skt) {
}

NetworkChannel::NetworkChannel(NetworkChannel&& other) : skt(other.skt) {
    move_action(other);
}

NetworkChannel& NetworkChannel::operator=(NetworkChannel&& other) {
    if (this == &other)
        return *this;

    move_action(other);
    return *this;
}
void NetworkChannel::move_action(NetworkChannel& other) {
    this->index = other.index;
    this->read_index = other.read_index;
    this->data = std::move(other.data);
    this->skt = std::move(other.skt);
    other.index = 0;
    other.read_index = 0;
}

void NetworkChannel::push_byte(const uint8_t value) {
    this->data.push_back(value);
    this->index++;
}

void NetworkChannel::push_short(const uint16_t value) {
    uint16_t transfer = htons(value);
    char* hostval = reinterpret_cast<char*>(&transfer);
    this->data.push_back(hostval[0]);
    this->data.push_back(hostval[1]);
    this->index += 2;
}

// Formato de comunicacion <Long de string> <String sin '\0'>
void NetworkChannel::push_string(const std::string &value) {
    this->push_short(value.size());

    for (auto letter : value)
        this->data.push_back(letter);
    this->index += value.size();
}

void NetworkChannel::push_uint(const uint32_t value) {
    uint32_t transfer = htonl(value);
    char* vals = reinterpret_cast<char*>(&transfer);
    this->data.push_back(vals[0]);
    this->data.push_back(vals[1]);
    this->data.push_back(vals[2]);
    this->data.push_back(vals[3]);
    this->index += 4;
}

uint8_t NetworkChannel::get_byte() {
    return this->data[this->index++];
}

uint16_t NetworkChannel::get_short() {
    uint16_t value = ((this->data[this->index+1] << 8) & 0xff00)
                    | (this->data[this->index] & 0x00ff);
    this->index += 2;
    return ntohs(value);
}

std::string NetworkChannel::get_string(const uint16_t size) {
    std::string message;
    message.resize(size);
    
    for (uint16_t i = 0; i < size; i++)
        message[i] = this->data[this->index+i];
    this->index += size;
    return message;
}

uint32_t NetworkChannel::get_uint() {
    uint32_t value = *reinterpret_cast<uint32_t*>(&this->data[this->index]);
    this->index += 4;
    return ntohl(value);
}

// Estas funciones estan para mantener privados los atributos del NetworkChannel
// Y para centralizar y no repetir el codigo
// encargado de envio de informacion por el socket
bool NetworkChannel::send() {
    bool was_closed = false;
    skt.sendall(&this->data[0], this->index, &was_closed);
    return !was_closed;
}

bool NetworkChannel::read(unsigned int msgSize) {
    if (this->data.size() < (this->read_index + msgSize)) {
        this->data.resize(this->read_index + msgSize);
    }

    bool was_closed = false;
    skt.recvall(&this->data[this->read_index], msgSize, &was_closed);
    this->read_index += msgSize;
    return !was_closed;
}

void NetworkChannel::clear() {
    this->index = 0;
    this->read_index = 0;
    this->data.clear();
}

uint8_t NetworkChannel::read_byte() {
    if (this->read(1))
        return this->get_byte();
    throw SocketConnectionLost();
}
uint16_t NetworkChannel::read_short() {
    if (this->read(2))
        return this->get_short();
    throw SocketConnectionLost();
}
uint32_t NetworkChannel::read_uint() {
    if (this->read(4))
        return this->get_uint();
    throw SocketConnectionLost();
}
// Formato de comunicacion <Long de string> <String sin '\0'>
std::string NetworkChannel::read_string() {
    uint16_t size = this->read_short();
    if (this->read(size))
        return this->get_string(size);
    throw SocketConnectionLost();
}


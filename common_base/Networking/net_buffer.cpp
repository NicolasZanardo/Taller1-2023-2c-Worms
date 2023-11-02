#include "net_buffer.h"
#include <arpa/inet.h>

NetBuffer::NetBuffer() :
    index(0),
    data()
    {}

void NetBuffer::push_byte(const uint8_t  value) {
    data.push_back(value);
    index++;
}

void NetBuffer::push_short(const uint16_t value) {
    uint16_t transfer = htons(value);
    char* hostval = reinterpret_cast<char*>(&transfer);
    
    data.push_back(hostval[0]);
    data.push_back(hostval[1]);
    index += 2;
}

void NetBuffer::push_uint(const uint32_t value) {
    uint32_t transfer = htonl(value);
    char* hostval = reinterpret_cast<char*>(&transfer);
    
    data.push_back(hostval[0]);
    data.push_back(hostval[1]);
    data.push_back(hostval[2]);
    data.push_back(hostval[3]);
    index += 4;
}

void NetBuffer::push_string(const string  &value) {
    push_short(value.size());

    for (auto letter : value)
        data.push_back(letter);
    index += value.size();
}

bool NetBuffer::send_by(Socket& channel) {
    bool was_closed = false;
    channel.sendall(&data[0], index, &was_closed);
    return !was_closed;

}

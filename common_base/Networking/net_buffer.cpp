#include "net_buffer.h"
#include <arpa/inet.h>
using namespace std;

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
    extend_by(2);
    
    data[index++] = hostval[0];
    data[index++] = hostval[1];
}

void NetBuffer::push_uint(const uint32_t value) {
    uint32_t transfer = htonl(value);
    char* hostval = reinterpret_cast<char*>(&transfer);
    
    extend_by(4);
    data[index++] = hostval[0];
    data[index++] = hostval[1];
    data[index++] = hostval[2];
    data[index++] = hostval[3];
}

void NetBuffer::push_string(const string  &value) {
    push_short(value.size());
    extend_by(value.size());

    for (auto letter : value)
        data[index++] = letter;
}

bool NetBuffer::send_by(Socket& channel) {
    bool was_closed = false;
    channel.sendall(&data[0], index, &was_closed);
    return !was_closed;

}

void NetBuffer::extend_by(int extension) {
    data.resize(data.size() + extension);
}

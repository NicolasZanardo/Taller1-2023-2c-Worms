#include "net_protocol_interpreter.h"
#include "socket_connection_lost_error.h"
#include <arpa/inet.h>
#include <vector>
using namespace std;

#define BYTE_SIZE 1
#define SHORT_SIZE 2
#define UINT_SIZE 4

NetProtocolInterpreter::NetProtocolInterpreter(Socket& channel) :
    channel(channel) {}

bool NetProtocolInterpreter::read_from_channel(char* buffer, int msgSize) {
    bool was_closed = false;
    channel.recvall(buffer, msgSize, &was_closed);
    return !was_closed;
}

uint8_t NetProtocolInterpreter::read_byte() {
    char buffer[BYTE_SIZE];
    if (read_from_channel(buffer, BYTE_SIZE)) {
        return buffer[0];
    }
    throw SocketConnectionLost(&channel);
}

uint16_t NetProtocolInterpreter::read_short() {
    char buffer[SHORT_SIZE];
    if (read_from_channel(buffer, SHORT_SIZE)) {
        return ntohs(*reinterpret_cast<uint16_t*>(buffer));
    }
    throw SocketConnectionLost(&channel);
}

uint32_t NetProtocolInterpreter::read_uint() {
    char buffer[UINT_SIZE];
    if (read_from_channel(buffer, UINT_SIZE)) {
        return ntohl(*reinterpret_cast<uint32_t*>(buffer));
    }
    throw SocketConnectionLost(&channel);
}

float NetProtocolInterpreter::read_float() {
    char buffer[UINT_SIZE];
    if (read_from_channel(buffer, UINT_SIZE)) {
        return ntohl(*reinterpret_cast<float*>(buffer));
    }
    throw SocketConnectionLost(&channel);
}

string NetProtocolInterpreter::read_string() {
    short size = read_short();
    vector<char> buffer;
    buffer.resize(size);
    
    if (read_from_channel(&buffer[0], size)) {
        return string(buffer.begin(),buffer.end());
    }
    throw SocketConnectionLost(&channel);
}

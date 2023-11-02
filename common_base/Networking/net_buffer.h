#ifndef COMMON_NET_BUFFER_H_
#define COMMON_NET_BUFFER_H_

#include <vector>
#include <string>
#include "../socket.h"
using namespace std;

class NetBuffer {
    uint32_t index;
    vector<char> data;

    public:
    NetBuffer();

    void push_byte(const uint8_t  value);
    void push_short(const uint16_t value);
    void push_uint(const uint32_t value);
    void push_string(const string  &value);

    bool send_by(Socket& channel);

    // Esta clase solo se usara en el stack que fue instanciada.
    private:
    NetBuffer(NetBuffer&&) = delete;
    NetBuffer& operator=(NetBuffer&&) = delete;
    NetBuffer(const NetBuffer &other) = delete;
    NetBuffer operator=(const NetBuffer &other) = delete;
};
#endif

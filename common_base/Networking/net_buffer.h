#ifndef COMMON_NET_BUFFER_H_
#define COMMON_NET_BUFFER_H_

#include <cstdint>
#include <vector>
#include <string>
#include "../socket.h"

class NetBuffer {
    uint32_t index;
    std::vector<char> data;
    void extend_by(int extension);

    public:
    NetBuffer();

    void push_byte(const uint8_t  value);
    void push_short(const uint16_t value);
    void push_uint(const uint32_t value);
    void push_float(const float value);
    void push_string(const std::string  &value);

    bool send_by(Socket& channel);

    // Esta clase solo se usara en el stack que fue instanciada.
    private:
    NetBuffer(NetBuffer&&) = delete;
    NetBuffer& operator=(NetBuffer&&) = delete;
    NetBuffer(const NetBuffer &other) = delete;
    NetBuffer operator=(const NetBuffer &other) = delete;
};
#endif

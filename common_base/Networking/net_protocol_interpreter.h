#ifndef COMMON_NET_PROTOCOL_INTERPRETER_H_
#define COMMON_NET_PROTOCOL_INTERPRETER_H_

#include <string>
#include <cstdint>
#include "../socket.h"

class NetProtocolInterpreter {
    Socket& channel;
    bool read_from_channel(char* buffer, int msgSize);

    public:
    explicit NetProtocolInterpreter(Socket& channel);

    uint8_t  read_byte  ();
    uint16_t read_short ();
    uint32_t read_uint  ();
    std::string   read_string();

    // Esta clase solo se usara en el stack que fue instanciada.
    private:
    NetProtocolInterpreter(NetProtocolInterpreter&&) = delete;
    NetProtocolInterpreter& operator=(NetProtocolInterpreter&&) = delete;
    NetProtocolInterpreter(const NetProtocolInterpreter &other) = delete;
    NetProtocolInterpreter operator=(const NetProtocolInterpreter &other) = delete;
};

#endif